-- Keep a log of any SQL queries you execute as you solve the mystery.
/* First things first : the schema of this database */
.schema

/* Now let's see the description of the crime scene */
SELECT description
FROM crime_scene_reports
WHERE year = 2021
AND month = 7
AND day = 28
AND street = "Humphrey Street";

/* There were 3 witnesses, let's look at their interviews */
SELECT transcript
FROM interviews
WHERE year = 2021
AND month = 7
AND day = 28;

/* We learned a lot there : first the thief fled with his car within 10 minutes after the theft.
Let's look at the bakery security logs to find the license plate of the car */
SELECT license_plate, minute
FROM bakery_security_logs
WHERE year = 2021
AND month = 7
AND day = 28
AND hour = 10
AND minute > 15
AND minute < 25;

/* We end up with a few license plates that could match.
Let's see the name of the owners to get our first suspect list */
SELECT name
FROM people
WHERE license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute > 15
    AND minute < 25
);

/* With the interviews we also learned that the thief withdrew money from the ATM on Legget Street earlier the day of the crime.
Let's take a look if any of our suspects withdrew money there this day */
SELECT DISTINCT name
FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE atm_location LIKE "Legget%"
AND name IN (
    SELECT name
    FROM people
    WHERE license_plate IN (
        SELECT license_plate
        FROM bakery_security_logs
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND hour = 10
        AND minute > 15
        AND minute < 25
    )
);

/* This narrows down our list of suspects.
Another piece of information we got from the interviews was that the thief was on phone for less than a minute leaving the bakery.
Let's compare the numbers of the calls respecting this points that matches with our suspects */
SELECT DISTINCT name
FROM people
JOIN phone_calls ON phone_calls.caller = people.phone_number
WHERE duration < 60
AND year = 2021
AND month = 7
AND day = 28
AND name IN (
    SELECT DISTINCT name
    FROM people
    JOIN bank_accounts ON bank_accounts.person_id = people.id
    JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
    WHERE atm_location LIKE "Legget%"
    AND name IN (
        SELECT name
        FROM people
        WHERE license_plate IN (
            SELECT license_plate
            FROM bakery_security_logs
            WHERE year = 2021
            AND month = 7
            AND day = 28
            AND hour = 10
            AND minute > 15
            AND minute < 25
        )
    )
);

/* This leaves only 2 suspects. To tell them apart, we can finally look for flights.
Indeed we learn with the interview that the thief takes the earliest flight out of fiftyville the 29th.
Let's compare our suspects' list with the passengers that took the first flight */
SELECT name
FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
JOIN flights ON flights.id = passengers.flight_id
WHERE flights.id = (
    SELECT flights.id
    FROM flights
    JOIN airports ON airports.id = flights.origin_airport_id
    WHERE full_name like "Fiftyville%"
    AND year = 2021
    AND month = 7
    AND day = 29
    ORDER BY hour, minute
    LIMIT 1
)
AND name IN (
    SELECT DISTINCT name
    FROM people
    JOIN phone_calls ON phone_calls.caller = people.phone_number
    WHERE duration < 60
    AND year = 2021
    AND month = 7
    AND day = 28
    AND name IN (
        SELECT DISTINCT name
        FROM people
        JOIN bank_accounts ON bank_accounts.person_id = people.id
        JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
        WHERE atm_location LIKE "Legget%"
        AND name IN (
            SELECT name
            FROM people
            WHERE license_plate IN (
                SELECT license_plate
                FROM bakery_security_logs
                WHERE year = 2021
                AND month = 7
                AND day = 28
                AND hour = 10
                AND minute > 15
                AND minute < 25
            )
        )
    )
);

/* We found the culprit ! Let's now figure out where Bruce has flown to.
Knowing that Bruce took the first flight of the 29th so let's find the city*/
SELECT city
FROM airports
JOIN flights ON flights.destination_airport_id = airports.id
JOIN passengers ON passengers.flight_id = flights.id
JOIN people ON people.passport_number = passengers.passport_number
WHERE name = "Bruce"
AND flights.id = (
    SELECT flights.id
    FROM flights
    JOIN airports ON airports.id = flights.origin_airport_id
    WHERE full_name like "Fiftyville%"
    AND year = 2021
    AND month = 7
    AND day = 29
    ORDER BY hour, minute
    LIMIT 1
);

/* Bruce fled to New York! Now we just need to find Bruce's accomplice.
Knowing that Bruce called his accomplice right after the theft, we got what we need to find his name */
SELECT name
FROM people
JOIN phone_calls ON phone_calls.receiver = people.phone_number
WHERE phone_calls.id = (
    SELECT phone_calls.id
    FROM phone_calls
    JOIN people ON people.phone_number = phone_calls.caller
    WHERE name = "Bruce"
    AND year = 2021
    AND month = 7
    AND day = 28
    AND duration < 60
);

/* The mystery is now fully solved !
The culprit is Bruce, he flew to New York and his accomplice is Robin ! */
