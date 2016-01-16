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

};

/////////////////////////////////////////////////////////////
// Static Manufacturer KB MAP
unordered_map<string, vector<string> > KB::manufacturerMap =
        {
                {"contax",      {"contax", "eddded"}},
                {"sanyo",       {"sanyo", "eddded"}},
                {"sigma",       {"sigma", "eddded"}},
                {"kyocera",     {"kyocera", "eddded"}},
                {"pentax",      {"pentax", "eddded"}},
                {"epson",       {"epson", "eddded"}},
                {"panasonic",   {"panasonic", "panasonic deutschland gmbh"}},
                {"agfa",        {"agfa", "eddded"}},
                {"casio",       {"casio", "eddded"}},
                {"samsung",     {"samsung", "samsung camera", "samsung digital"}},
                {"fujifilm",    {"fujifilm", "fugi finepix", "fuji"}},
                {"konica minolta", {"konica minolta", "konica"}},
                {"canon",       {"canon", "eddded"}},
                {"ricoh",       {"ricoh", "eddded"}},
                {"leica",       {"leica", "eddded"}},
                {"olympus",     {"olympus", "eddded"}},
                {"hp",          {"hp", "h-p"}},
                {"sony",        {"sony", "sony mobile", "sony computer"}},
                {"kodak",       {"kodak", "kodak film"}},
                {"nikon",       {"nikon", "eddded"}},
                {"toshiba",       {"toshiba", "eddded"}},
        };
