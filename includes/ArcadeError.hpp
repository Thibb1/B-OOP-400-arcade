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
        explicit ArcadeError(Error Message = "An error occurred") :
            ErrorMessage("./arcade: " + std::move(Message)) {}
        [[nodiscard]] const char *what() const noexcept override {
            return ErrorMessage.c_str();
        }
    };

    class ArcadeUsageError : public  ArcadeError {
    public:
        explicit ArcadeUsageError(Error Message = "\nUSAGE: ./arcade ./lib/arcade_(graphic_lib).so") :
            ArcadeError(std::move(Message)) {}
    };

    class ArcadeRuntimeError : public ArcadeError {
    public:
        explicit ArcadeRuntimeError(Error Message = "A runtime error occurred") :
            ArcadeError(std::move(Message)) {}
    };

    class ArcadeMissingError : public  ArcadeError {
    public:
        explicit ArcadeMissingError(Error Message = "Missing element error occurred") :
            ArcadeError("Missing: " + std::move(Message)) {}
    };
}