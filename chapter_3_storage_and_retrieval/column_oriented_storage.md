* Data is stored by columns as opposed to rows stored right next to each in disk storage storage.

#### Column Compression
* The nice thing about column-oriented storage is that values within a column are usually very similar or of the same type. This allows us to encode the data and make it smaller.
	* Examples of encodings:
		* Bitmap encoding
        **Example of bitmap encoding**
        ![Bitmap encoding image](bitmap_encoding_store_key_column.png)
		* Run-length encoding
        **Example of RLE**
        ![RLE image](run_length_encoding_of_sparse_bitmap.png)
* **Sort Order in Column Storage**: Allows encodings to be more efficient and smaller since similar values are right next to each other.
