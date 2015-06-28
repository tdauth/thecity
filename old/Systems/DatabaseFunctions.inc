//*******************************************************************
//Database Functions
//*******************************************************************
#if defined DatabaseFunctions_included
  	#endinput
#endif
#define DatabaseFunctions_included
#pragma library DatabaseFunctions

//-- Functions --
DatabaseFileExists(FileName[])
{
	return fexist(FileName);
}

RemoveDatabaseFile(FileName[])
{
	fremove(FileName);
	return true;
}

CopyDatabaseFileHandle(File:UsedFile, File:NewFile, Close = true)
{
	new Line[MAX_STRING];
 	while (fread(UsedFile, Line))
  	{
   		fwrite(NewFile, Line);
	}
	if (Close)
	{
		fclose(UsedFile);
		fclose(NewFile);
	}
	return true;
}

File:CopyDatabaseFile(FileName[], NewFileName[], Close = true)
{
	if (strcmp(FileName, NewFileName, true) != 0)
 	{
 	    new File:UsedFile = fopen(FileName, io_read);
 	    new File:NewFile = fopen(NewFileName, io_write);
 	    CopyDatabaseFileHandle(UsedFile, NewFile, Close);
		return NewFile;
 	}
 	return false;
}

//Wegen Remove nur ohne Handles möglich
File:RenameDatabaseFile(FileName[], NewFileName[])
{
    new File:NewFile = CopyDatabaseFile(FileName, NewFileName);
	RemoveDatabaseFile(FileName);
	return NewFile;
}

SaveDatabaseFHValueString(File:UsedFile, Label[], Value[], Close = true) //SaveDatabaseFileHandleValueString
{
    new NewLine[MAX_STRING];
	format(NewLine, sizeof(NewLine), "%s = %s\r\n", Label, Value); //Überprüfen ob \r und \n auch als Zeichen zählen. Wenn, dann werden sie auch als Wert ausgewertet
	fwrite(UsedFile, NewLine);
	if (Close)
	{
		fclose(UsedFile);
	}
	return true;
}

SaveDatabaseFileHandleInteger(File:UsedFile, Label[], Value, Close = true)
{
	new StringValue[MAX_STRING];
	valstr(StringValue, Value);
	SaveDatabaseFileHandleValueString(UsedFile, Label, StringValue, Close);
	return true;
}

SaveDatabaseFileHandleFloat(File:UsedFile, Label[], Float:Value, Close = true)
{
	new StringValue[MAX_STRING];
	valstr(StringValue, int(Value)); //Man kann einen float nicht direkt in einen String umwandeln
    SaveDatabaseValueString(UsedFile, Label, StringValue, Close);
    return true;
}

File:SaveDatabaseFileValueString(FileName[], Label[], Value[], Close = true)
{
	new File:UsedFile = fopen(FileName, io_append);
	SaveDatabaseFHValueString(UsedFile, Label, Value, Close);
	return UsedFile;
}

File:SaveDatabaseFileInteger(FileName[], Label[], Value, Close = true)
{
	new StringValue[MAX_STRING];
	valstr(StringValue, Value);
	return SaveDatabaseFileValueString(FileName, Label, StringValue, Close);
}

File:SaveDatabaseFileFloat(FileName[], Label[], Float:Value, Close = true)
{
	new StringValue[MAX_STRING];
	valstr(StringValue, int(Value)); //Man kann einen float nicht direkt in einen String umwandeln
    return SaveDatabaseFileValueString(FileName, Label, StringValue, Close);
}

GetDatabaseFHValueString(File:UsedFile, Label[], Close = true) //GetDatabaseFileHandleValueString
{
	new Line[MAX_STRING];
	new LineLabelPosition;
	new LineValue[MAX_STRING] = "Empty";
	new Index;
	new DebugI0 = 0;
	//Check The File For The Line
	while(fread(UsedFile, Line))
	{
  		LineLabelPosition = strfind(Line, Label, true);
		//Is The Line We Need
		if (LineLabelPosition != -1)
  		{
  		    LineValue = Strtok(Line, Index);
  		    if (strcmp(LineValue, "=", true) == 0)
  		    {
  		        LineValue = Strtok(Line, Index);
			}
			else
			{
			    printf("File Reading Error: Line %d. Can't find '='.", DebugI0);
			}
			break;
	 	}
	 	DebugI0++;
	}
	if (Close)
	{
		fclose(UsedFile);
	}
	return true;
}

GetDatabaseFileValueString(FileName[], Label[], Close = true)
{
    new File:UsedFile = fopen(FileName, io_read);
	return GetDatabaseFileHandleValueString(UsedFile, Label, Close);
}

GetDatabaseFileInteger(FileName[], Label[], Close = true)
{
	return strval(GetDatabaseValueString(FileName, Label, Close));
}

Float:GetDatabaseFileFloat(FileName[], Label[], Close = true)
{
	return floatstr(GetDatabaseValueString(FileName, Label, Close));
}
