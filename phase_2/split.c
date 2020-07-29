#include "split.h"

int splitcode(thread_param_t* threadList, int threadCount, int rows, int columns)
{
  
    if ((rows / threadCount) != 0)
    {
        int extraRows = rows % threadCount;
        int maxPer = rows / threadCount;

        int currentRow = 0;
        for (int i = 0; i < threadCount; ++i)
        {
            if (extraRows > 0)
            {
                threadList[i].firstRow = currentRow;
                threadList[i].firstCol = 0;
                threadList[i].length = (maxPer + 1) * columns;
                currentRow += maxPer + 1;
                --extraRows;
            }
            else
            {
                threadList[i].firstRow = currentRow;
                threadList[i].firstCol = 0;
                threadList[i].length = maxPer * columns;
                currentRow += maxPer;
            }
        }
    }
    
    else if (threadCount > (rows * columns))
    {
        int overflow = 0;
        overflow = threadCount - (rows * columns);
        int currentRow = 0;
        int currentCol = 0;

        for (int i = 0; i < threadCount; ++i)
        {
            if ((threadCount - i) > overflow)
            {
                threadList[i].firstRow = currentRow;
                threadList[i].firstCol = currentCol;
                threadList[i].length = 1;

                if ((currentCol + 1) >= columns)
                {
                    currentCol = 0;
                    ++currentRow;
                }
                else
                {
                    ++currentCol;
                }
            }
            else
            {
                
                threadList[i].firstRow = 0;
                threadList[i].firstCol = 0;
                threadList[i].length = 0;
            }
        }
    }
  
    else
    {
        int currentRow = 0;
        int currentCol = 0;

        for (int i = 0; i < threadCount; ++i)
        {
            
            if ((threadCount - i) > (rows - currentRow))
            {
                threadList[i].firstRow = currentRow;
                threadList[i].firstCol = currentCol;
                threadList[i].length = 1;

                if ((currentCol + 1) >= columns)
                {
                    currentCol = 0;
                    ++currentRow;
                }
                else
                {
                    ++currentCol;
                }
            }
            else
            {
               
                if (currentCol != 0)
                {
                    int columnsLeft = columns - currentCol;
                    threadList[i].firstRow = currentRow;
                    threadList[i].firstCol = currentCol;
                    threadList[i].length = columnsLeft;

                    currentCol = 0;
                    ++currentRow;
                }
                else
                {
                    threadList[i].firstRow = currentRow;
                    threadList[i].firstCol = currentCol;
                    threadList[i].length = columns;

                    ++currentRow;
                }
            }
        }
    }

    return 0;
}
