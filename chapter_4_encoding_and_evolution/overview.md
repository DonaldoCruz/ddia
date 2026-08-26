# Chapter 4: Encoding & Evolution

**Backward compatibility**: new code that works with old data.

**Forward compatibility**: old code that works or will work, with future data.

## Encodings
* **Encoding**: when you want to write data to a file or send it over the network, encoding is the process of 
    taking that in-memory data, and turning it into a self-contained sequence of bytes. (Synonyms for encoding is serialization and mashalling. Serialization has 
    a different meaning in the context of transactions.)

    * There exists language specific encoding format but they are not reliable because a different programming languague would have trouble decoding/deserializing/unmarshalling 
    that encoded data. This is where standard encoding formats come in. (e.g., python=pickle, java=java.io.Serializable, ruby=Marshal)

    * This where standardized encoding come in. Encoding formats like JSON, XML, CSV are textual formats, making them somewhat human readable.
        * Each format has its own pros and cons. XML and CSV lack the ability to differentiate between numbers and strings that happen to consist of digits (e.g., "123").
        * JSON on the other hand is able to distinguish between numbers and strings, but it cannot distinguish between integers and floating-point numbers, and doesn't specify a precision.
        This is a big problem when dealing with big numbers because they become inaccurate.
        Another limitation that JSON and XML formats have is that they cannot represent binary strings (sequences of bytes without a character encoding). To get around this
        you can usually use base64 character encoding but it will increase your data size by 33%.
        Both JSON and XML have schema support. CSV on the other hand does not have any schema.
        * Both XML and JSON use a lot of space, this is where **binary encoding** formats come in (MessagePack, BSON, BJSON, UBJSON, WBXML).They decrease the amount of data size but
        are not human-readable.


