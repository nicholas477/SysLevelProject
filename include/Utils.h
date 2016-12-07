// Splits a string into an array of substrings
static void SplitString(char* InString, char Delim, char** OutStrings, int OutStringsLen)
{
    int i = 0;
    char* LastLine = &InString[0];
    int LineNum = 0;
    int InStringLen = strlen(InString);

    while (InString[i] && LineNum < OutStringsLen)
    {
        // If we have hit a delimiter char or we're at the end of the string
        if (InString[i] == Delim)
        {
            InString[i] = '\0';
            if (strlen(LastLine) > 0)
            {
                OutStrings[LineNum] = LastLine;
                LineNum++;
            }
            LastLine = &InString[i + 1];
        }
        else if (i == InStringLen - 1)
        {
            OutStrings[LineNum] = LastLine;
            return;
        }

        i++;
    }
}

static bool IsStringNumber(const char* Input)
{
    if (strlen(Input) == 0)
        return false;

    for (int i = 0; i < strlen(Input); i++)
    {
        if (Input[i] < '0' || Input[i] > '9')
            return false;
    }

    return true;
}