import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Select the user's current cash balance
    user = db.execute("SELECT * FROM users WHERE id = ?",
                      session["user_id"])
    cash = round(user[0]["cash"], 2)

    # Select the user's shares per stock
    shares = db.execute("SELECT stock_symbol, total_shares FROM shares WHERE user_id = ?",
                        session["user_id"])

    # Create the user's portfolio and the sum of all his stocks
    portfolio = []
    total_stocks = 0
    for share in shares:
        stock = {}
        quote = lookup(share["stock_symbol"])
        stock["symbol"] = share["stock_symbol"]
        stock["shares"] = share["total_shares"]
        stock["price"] = quote["price"]
        total = round(share["total_shares"] * quote["price"], 2)
        total_stocks += total
        stock["total"] = total
        portfolio.append(stock)
    total_stocks = round(total_stocks, 2)

    # Caculate total balance
    balance = cash + total_stocks

    # Renders the user's portfolio
    return render_template("index.html", portfolio=portfolio, cash=cash, total_stocks=total_stocks, balance=balance)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure a symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide stock symbol", 400)

        # Look up for the stock quote
        quote = lookup(request.form.get("symbol"))

        # Ensure the stock symbol exists
        if not quote:
            return apology("stock symbol does not exist", 400)

        # Ensure a number of shares was submitted
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("must provide an integer for shares", 400)

        # Ensure the number of shares is a positive integer
        if shares < 1:
            return apology("shares must be a positive integer", 400)

        # Ensure the user has enough cash to buy the stock share(s)
        cost = quote["price"] * shares
        user = db.execute("SELECT * FROM users WHERE id = ?",
                          session["user_id"])
        cash = user[0]["cash"]
        if cost > cash:
            return apology("not enough cash", 400)

        # Add the transaction to the transactions database
        db.execute("INSERT INTO transactions (user_id, buying, stock_symbol, stock_price, stock_shares, time) VALUES (?, ?, ?, ?, ?, ?)",
                   session["user_id"], True, quote["symbol"], quote["price"], shares, datetime.now())

        # Check if the user already has some shares of the stock
        stock = db.execute("SELECT * FROM shares WHERE user_id = ? AND stock_symbol = ?",
                           session["user_id"], quote["symbol"])

        # Add the shares to the shares database
        if len(stock) == 0:
            db.execute("INSERT INTO shares (user_id, stock_symbol, total_shares) VALUES (?, ?, ?)",
                       session["user_id"], quote["symbol"], shares)
        else:
            new_total_shares = stock[0]["total_shares"] + shares
            db.execute("UPDATE shares SET total_shares = ? WHERE user_id = ? AND stock_symbol = ?",
                       new_total_shares, session["user_id"], quote["symbol"])

        # Remove the expense from the user's total cash
        new_total = cash - cost
        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   new_total, session["user_id"])

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Select the user's transaction history
    transactions = db.execute("SELECT * FROM transactions WHERE user_id = ?",
                              session["user_id"])

    # Renders the user's history
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?",
                          request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure a symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide stock symbol", 400)

        # Look up for the stock quote
        quote = lookup(request.form.get("symbol"))

        # Ensure the stock symbol exists
        if not quote:
            return apology("stock symbol does not exist", 400)

        # Render a page with the stock quote
        return render_template("quoted.html", quote=quote)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure password confirmation was submitted
        elif not request.form.get("confirmation"):
            return apology("must provide password confirmation", 400)

        # Ensure password confirmation was submitted
        elif request.form.get("confirmation") != request.form.get("password"):
            return apology("password and confirmation do not match", 400)

        # Hash the password of the user
        hash = generate_password_hash(request.form.get("password"))

        # Add the user to the database
        try:
            db.execute("INSERT INTO users (username, hash) VALUES(?, ?)",
                       request.form.get("username"), hash)
        except:
            return apology("username already taken", 400)

        # Store the id of the last row
        rows = db.execute("SELECT * FROM users WHERE username = ?",
                          request.form.get("username"))

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure a symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide stock symbol", 400)

        # Look up for the stock quote
        quote = lookup(request.form.get("symbol"))

        # Ensure the user has shares left to sell
        stock = db.execute("SELECT * FROM shares WHERE user_id = ? AND stock_symbol = ?",
                           session["user_id"], quote["symbol"])
        if not stock:
            return apology("no more shares left to sell", 400)

        # Ensure a number of shares was submitted
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("must provide an integer for shares", 400)

        # Ensure the number of shares is a positive integer
        if shares < 1:
            return apology("shares must be a positive integer", 400)

        # Ensure the user has enough shares to sell
        total_shares = stock[0]["total_shares"]
        if shares > total_shares or not total_shares:
            return apology("not enough shares to sell", 400)

        # Add the transaction to the transactions database
        db.execute("INSERT INTO transactions (user_id, buying, stock_symbol, stock_price, stock_shares, time) VALUES (?, ?, ?, ?, ?, ?)",
                   session["user_id"], False, quote["symbol"], quote["price"], shares, datetime.now())

        # Remove the shares from the shares database
        if shares == total_shares:
            db.execute("DELETE FROM shares WHERE user_id = ? AND stock_symbol = ?",
                       session["user_id"], quote["symbol"])
        else:
            new_total_shares = stock[0]["total_shares"] - shares
            db.execute("UPDATE shares SET total_shares = ? WHERE user_id = ? AND stock_symbol = ?",
                       new_total_shares, session["user_id"], quote["symbol"])

        # Add the cash to the user's total cash
        proceeds = quote["price"] * shares
        user = db.execute("SELECT * FROM users WHERE id = ?",
                          session["user_id"])
        cash = user[0]["cash"]
        new_total = cash + proceeds
        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   new_total, session["user_id"])

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        stocks = db.execute("SELECT stock_symbol FROM shares WHERE user_id = ?",
                            session["user_id"])
        return render_template("sell.html", stocks=stocks)


@app.route("/add_cash", methods=["GET", "POST"])
@login_required
def add_cash():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure number is submitted
        try:
            cash = round(float(request.form.get("cash")), 2)
        except:
            return apology("must provide a number", 400)

        # Ensure a positive value is submitted
        if cash < 1.0:
            return apology("must provide a positive value", 400)

        # Add the amount to the user's total cash
        user = db.execute("SELECT * FROM users WHERE id = ?",
                          session["user_id"])
        total_cash = user[0]["cash"]
        new_total = total_cash + cash
        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   new_total, session["user_id"])

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("add_cash.html")
