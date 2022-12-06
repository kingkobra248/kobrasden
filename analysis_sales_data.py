# import necessary libraries prerequisite for data analysis, wrangli
# ng and visualizatio

# library for data visualizations
import matplotlib.pyplot as plot
import numpy as np
import pandas as pd

# reading data
sales_dataset = pd.read_csv('c:/users/user/Desktop/Spss/salesdata.csv', header=0, index_col=None, encoding='latin-1')
# print(sales_dataset)

# print(sales_dataset.columns)

sales_dataset_subset = sales_dataset[
    ['ORDERDATE', 'ORDERNUMBER', 'ORDERLINENUMBER', 'PRODUCTLINE', 'QUANTITYORDERED', 'PRICEEACH', 'SALES', 'STATUS']]

print(sales_dataset_subset.describe())

copy_of_renamed_sales_dataset_subset = sales_dataset_subset.copy()
copy_of_renamed_sales_dataset_subset.rename(columns={'ORDERNUMBER': 'Order Id',
                                                     'PRICEEACH': 'Price',
                                                     'SALES': 'Revenue'},
                                            inplace=True)

X_Y = copy_of_renamed_sales_dataset_subset.groupby(['PRODUCTLINE'])['Revenue'].sum().sort_values(ascending=False)
bar_graph = X_Y.plot(kind='bar', title='Product line and revenue')
plot.show()


X_Y_line= copy_of_renamed_sales_dataset_subset.groupby(['PRODUCTLINE'])['Revenue'].sum().nlargest(5)

print(X_Y_line)

line = X_Y_line.plot(kind='line', title='Top 5 products')




plot.show()


