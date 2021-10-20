from typing import List


class DataFile:
    """DataFile class can read tab separated text file include some text at the 
    bottom of the file.

    The following file format is expected.
    1. The file is '.txt' file and lists tab separated values.
    2. The first row is only column names, not raw data.
    3. Raw data part of the first column must start with the second row and not include 
        empty row.
    4. There is at least one empty row between last row of raw data and some text 
        at the bottom of the file.
    5. The data rows of all columns is same.

    Attributes:
        file_path: A path to text file.
    """

    def __init__(self, file_path: str):
        """Inits DataFile with text file path."""
        with open(file_path) as f:
            file_content = f.readlines()
        for i, line in enumerate(file_content):
            line = line.split('\t')
            line[-1] = line[-1].replace('\n', '')
            file_content[i] = line
        self.file_content = file_content
    
    def get_column_names(self) -> List[str]:
        """Get column names from given file.
        
        Returns:
            Column names.
        """
        return self.file_content[0]

    def get_column_length(self) -> int:
        """Get column length from given file.

        Return data length per one column (include columun name row). 
        Expected data format: The last data row is just one row above empty row and
        no empty cell in first data column. In addition, first data column's length must be 
        equal to other's.
        
        Returns:
            Column length.
        """
        column_length: int = 0
        for line in self.file_content:
            if line[0] != '':
                column_length += 1
            else:
                break
        return column_length
    
    def get_column(self, column_name: str, return_column_name=False) -> List[float]:
        """Get single data column of given name.

        Return single data column. Column name must set in the first row of the column.
        In addition, data between sencond and last row should float at least number. 
        
        Args:
        column_name: The column name of the data you want.
        return_column_name: If you want to include the column name as the first element 
        of returned list, you can alse set this value True.

        Returns:
            Flaot column data.
        """
        indices = self.get_column_names().index(column_name)
        column_length = self.get_column_length()
        column = []
        for i, line in enumerate(self.file_content):
            if i == 0:
                column_name = line[indices]
            elif i < column_length:
                value = line[indices] 
                column.append(float(value))
            else:
                break
        if return_column_name:
            return column, column_name
        return column
