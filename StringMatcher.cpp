///////////////////////////////////////////////////////////////
// Created by Jeremy on 1/10/2016.
///////////////////////////////////////////////////////////////

#include "StringMatcher.h"

/////////////////////////////////////////////////////////////
// Static Invalid Char Map
unordered_set<char> KB::invalidCharMap =
        {
                ':',
                '[',
                ']',
                ';',
                '\'',
                '\"',
                '-',
                '_',
                '+',
                '=',
                '|',
                '/',
                '?',
                '<',
                '>',
                '.',
                ',',
                '!',
                '@',
                '#',
                '$',
                '%',
                '^',
                '*',
                '(',
                ')',
                '~',
        };


/////////////////////////////////////////////////////////////
// Static Invalid Char Map
unordered_set<string> KB::ambiguousWordMap =
{
    "digital",
};


/////////////////////////////////////////////////////////////
// Static Invalid Char Map
unordered_set<string> KB::invalidWordMap =
{
    "",
    "camera",
    "digital",
    "true",

};

/////////////////////////////////////////////////////////////
// Static Manufacturer KB MAP
unordered_map<string, vector<string> > KB::manufacturerMap =
        {
                {"contax",      {"contax", }},
                {"sanyo",       {"sanyo", }},
                {"sigma",       {"sigma", }},
                {"kyocera",     {"kyocera", }},
                {"pentax",      {"pentax", }},
                {"epson",       {"epson", }},
                {"panasonic",   {"panasonic", "panasonic deutschland gmbh"}},
                {"agfa",        {"agfa", }},
                {"casio",       {"casio", }},
                {"samsung",     {"samsung", "samsung camera", "samsung digital"}},
                {"fujifilm",    {"fujifilm", "fugi finepix", "fuji"}},
                {"konica minolta", {"konica minolta", "konica"}},
                {"canon",       {"canon", "canon ltd", "canon canada" }},
                {"ricoh",       {"ricoh",}},
                {"leica",       {"leica", }},
                {"olympus",     {"olympus", }},
                {"hp",          {"hp", "h-p", "hewlett packard", "hewlettpackard"}},
                {"sony",        {"sony", "sony mobile", "sony computer"}},
                {"kodak",       {"kodak", "kodak film"}},
                {"nikon",       {"nikon", }},
                {"toshiba",       {"toshiba", }},
        };
