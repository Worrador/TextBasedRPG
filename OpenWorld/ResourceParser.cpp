#include "ResourceParser.h"


ResourceParser::ResourceParser()
{
    // Open the Excel file
    CELFile file("Items.xlsx");

    // Create a database from the Excel file
    CELDatabase database(file);

    // Iterate through the sheets in the Excel file
    for (int i = 0; i < database.GetSheetCount(); i++)
    {
        // Get the sheet at the current index
        CELSheet sheet = database.GetSheet(i);


        // Iterate through the rows in the sheet
        for (int j = 0; j < sheet.GetRowCount(); j++)
        {
            // Get the row at the current index
            CELRow row = sheet.GetRow(j);

            // Iterate through the cells in the row
            for (int k = 0; k < row.GetCellCount(); k++)
            {
                // Get the cell at the current index
                CELValue cell = row.GetCell(k);

                // Do something with the cell value
                // ...
            }
        }
    }
}


ResourceParser::~ResourceParser() 
{

}