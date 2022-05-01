-- Keep a log of any SQL queries you execute as you solve the mystery.

-- 1st look for the description of the scene by using the crime_scene_reports table
SELECT description FROM crime_scene_reports WHERE year = 2020 AND street = "Chamberlin Street" AND day = 28 AND month = 7;
-- according to the description the theft took place at --> "10:15AM" !!!
-- 3 witnesses who were there at 10:15Am
-- Each of their interview transcripts mentions the courthouse
SELECT transcript FROM interviews WHERE year = 2020 AND month = 7 AND day = 28;

-- we need interviews
-- One interview --> within 10 mins of the theft; thief get into car in the courhouse parking lot. We should see security footage parking lot of the courthouse.
-- Check cars around that time.
-- We have year month day hour ~minute and activity information from courthouse. We can get car's plate -->  license_plate
SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND day = 28 AND month = 7 AND hour = 10 AND minute > 15 AND minute < 25 AND activity = "exit";

-- One interview --> walking by the - ATM on Fifer Street - thief withdrawing money
-- using atm_transactions narrow down the account number
SELECT account_number FROM atm_transactions WHERE year = 2020 AND day = 28 AND month = 7 AND atm_location = "Fifer Street" AND transaction_type LIKE "%withdraw%";

-- Thief called someone less than 1 min while leaving.
-- Use the provided information, provide phone numbers
SELECT caller FROM phone_calls WHERE year = 2020 AND day = 28 AND month = 7 AND duration < 60;

-- Planning to take earlies flight out of Fiftyville tomorrow (29)
-- See the flights out of town. order by date
-- Find the airport first
SELECT id FROM airports WHERE city = "Fiftyville";
-- id -> 8 // abbreviation -> "CSF" // full name -> "Fiftyville Regional Airport"

SELECT id FROM flights WHERE year = 2020 AND day = 29 AND month = 7 AND origin_airport_id = 8 ORDER BY hour;
-- flight id = 36 for the earliest flight to out of town

-- get passport numbers of the passengers who took the flight, hard-coded flight number
SELECT passport_number from passengers WHERE flight_id = 36;

-- Nest all the information to see what we got so far
-- Used information ; 1) suspecious license_plates from courthouse secuirty w/ provided info
-- 2) suspecious phone numbers who make the call under 60 seconds
-- 3) passport number from passengers who took the flight 36, which is the earliest flight on 29/7/2020
SELECT name FROM people WHERE license_plate IN
(SELECT license_plate FROM courthouse_security_logs
WHERE year = 2020 AND day = 28 AND month = 7 AND hour = 10 AND minute > 15 AND minute < 25 AND activity = "exit")
AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND day = 28 AND month = 7 AND duration < 60)
AND passport_number IN (SELECT passport_number from passengers WHERE flight_id = 36);
-- We narrow down to 3 suspecious
-- we can use this people to see who were called

-- Join the bank_accounts to people ON id to narrow it down.
SELECT name FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE license_plate IN
(SELECT license_plate FROM courthouse_security_logs
WHERE year = 2020 AND day = 28 AND month = 7 AND hour = 10 AND minute > 15 AND minute < 25 AND activity = "exit")
AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND day = 28 AND month = 7 AND duration < 60)
AND passport_number IN (SELECT passport_number from passengers WHERE flight_id = 36)
AND account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND day = 28 AND month = 7
AND atm_location = "Fifer Street" AND transaction_type LIKE "%withdraw%");
-- as a result of this query we ended up with "Ernest", who is the thief !!

-- In order to find where they went to;
-- Use the earliest flight id.

SELECT destination_airport_id FROM flights WHERE id IN (SELECT id FROM flights WHERE year = 2020
AND day = 29 AND month = 7 AND origin_airport_id = 8 ORDER BY hour LIMIT 1);

-- Use the destination airport id to find the city, where they escaped to;
SELECT city FROM airports WHERE id IN (SELECT destination_airport_id FROM flights
WHERE id IN (SELECT id FROM flights WHERE year = 2020
AND day = 29 AND month = 7 AND origin_airport_id = 8 ORDER BY hour LIMIT 1));
-- They escaped to "London" !!

-- In order to find the accomplice use phone calls, which is less than a minute
SELECT receiver FROM phone_calls WHERE caller IN
(SELECT phone_number FROM people WHERE name = "Ernest")
AND year = 2020 AND day = 28 AND month = 7 AND duration < 60;

-- Find the name of the accomplice from the receiver's number;
SELECT name FROM people WHERE phone_number IN
(SELECT receiver FROM phone_calls WHERE caller IN
(SELECT phone_number FROM people WHERE name = "Ernest")
AND year = 2020 AND day = 28 AND month = 7 AND duration < 60);
-- Accomplice is "Berthold" !!