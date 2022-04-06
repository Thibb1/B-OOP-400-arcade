/*
** EPITECH PROJECT, 2022
** ArcadeError
** File description:
** TODO
*/

#pragma once

#include <string>
#include <exception>
#include <iostream>

namespace Arcade
{
    typedef std::string Error;
    class ArcadeError : public std::exception {
    private:
        const Error ErrorMessage;
    public:
        /**
         * It takes an error message as a parameter, and then constructs an
         * ArcadeError object with that message
         *
         * @param Message The error message to display.
         */
        explicit ArcadeError(Error Message = "An error occurred") :
            ErrorMessage("./arcade: " + std::move(Message)) {}
        /**
         * Return the error message
         *
         * @return Nothing.
         */
        [[nodiscard]] const char *what() const noexcept override {
            return ErrorMessage.c_str();
        }
    };

    class ArcadeUsageError : public  ArcadeError {
    public:
        /**
         * This function is a constructor for the ArcadeUsageError class
         *
         * @param Message The error message to be displayed.
         */
        explicit ArcadeUsageError(Error Message = "\nUSAGE: ./arcade ./lib/arcade_(graphic_lib).so") :
            ArcadeError(std::move(Message)) {}
    };

    class ArcadeRuntimeError : public ArcadeError {
    public:
        /**
         * It's a constructor that takes an error message as an argument and uses
         * it to initialize the error message of the base class
         *
         * @param Message The message to be displayed.
         */
        explicit ArcadeRuntimeError(Error Message = "A runtime error occurred") :
            ArcadeError(std::move(Message)) {}
    };

    class ArcadeMissingError : public  ArcadeError {
    public:
        /**
         * The function is a constructor for the ArcadeMissingError class
         *
         * @param Message The error message to be displayed.
         */
        explicit ArcadeMissingError(Error Message = "Missing element error occurred") :
            ArcadeError("Missing: " + std::move(Message)) {}
    };
}