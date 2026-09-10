# Chapter 4: Encoding & Evolution

**Backward compatibility**: new code that works with old data.

**Forward compatibility**: old code that works or will work, with future data.

## Encodings
* **Encoding**: when you want to write data to a file or send it over the network, encoding is the process of 
    taking that in-memory data, and turning it into a self-contained sequence of bytes. (Synonyms for encoding is serialization and mashalling. Serialization has 
    a different meaning in the context of transactions.)

    * There exists language specific encoding format but they are not reliable because a different programming languague would have trouble decoding/deserializing/unmarshalling 
    that encoded data. This is where standard encoding formats come in. (e.g., python=pickle, java=java.io.Serializable, ruby=Marshal)

    * This is where standardized encoding come in. Encoding formats like JSON, XML, CSV are textual formats, making them somewhat human readable.
        * Each format has its own pros and cons. XML and CSV lack the ability to differentiate between numbers and strings that happen to consist of digits (e.g., "123").
        * JSON on the other hand is able to distinguish between numbers and strings, but it cannot distinguish between integers and floating-point numbers, and doesn't specify a precision.
        This is a big problem when dealing with big numbers because they become inaccurate.
        Another limitation that JSON and XML formats have is that they cannot represent binary strings (sequences of bytes without a character encoding). To get around this
        you can usually use base64 character encoding but it will increase your data size by 33%.
        Both JSON and XML have schema support. CSV on the other hand does not have any schema.
        * Both XML and JSON use a lot of space, this is where **binary encoding** formats come in (MessagePack, BSON, BJSON, UBJSON, WBXML).They decrease the amount of data size but
        are not human-readable.


    ### Binary Encodings

    * **Protocol Buffers**: Developed by Google, it is a binary encoding format.
        ```
        message Person {
            required string user_name           = 1;
            optional int64 favorite_number      = 2;
            repeated string interests           = 3;
        }
        ```

    * **Thrift**: Developed by Facebook. Has two different encoding formats, BinaryProtocol and CompactProtocol
        ```
        struct Person {
            1: required string      user_name,
            2: optional int64       favorite_number,
            3: repeated string      interests
        }
        ```
    * Protocol Buffers and Thrist protocols use field tags as opposed to storing field names. Field tags are just integers that map to the field names.

    * **Avro**: Started as a subproject of Hadoop because of the incompatibility Thrift had in Hadoop. Avro has two different schema languages, Avro IDL and JSON. Avro IDL
    is meant to be more human readable while the JSON schema of avro is meant to be more machine readable.

        Avro IDL Example
        ```
        record Person {
            string                  username;
            union { null, long }    favoriteNumber = null;
            array<string>           interests;
        }
        ```

        Avro JSON schema
        ```JSON
        {
            "type": "record",
            "name": "Person",
            "fields": {
                {"name": "username",        "type": "string"},
                {"name": "favoriteNumber",  "type": [ "null", "long" ], "default": null},
                {"name": "interests",       "type": { "type": "array", "items": "string"}},
            }
        }
        ```

        * Avro uses variable length encoding, along with zigzag encoding. I am not too familiar with these encoding methods.
        * **Schema evolution in Avro**: Applications using Avro must have two schemas, one at the writer (encoder), and one at the reader (decoder).
            * If a field is missing in the reader schema that the writer schema has, it just ignores it.
            * If a field expected by the reader schema is missing that the writer schema does not populate, it just assigns the default value to it.

            * **Forward compatibility**: It means that writers have a new schema while readers have the old schema.
            * **Backward compatibility**: It means that writers have an old schema while readers have the new schema.

            * Schema evolution is Avro is dynamic, and can be done easily. The only thing that updates are the schemas on the writer, and a conversion is done when writing
            with the new schema.

    * **Code Generation**: Thrift and Protocol Buffers rely on code generation after a schema has been defined to implement the schema. It usefule to choose a 
    statically typed programming language like C++ or Java because it allows efficient in-memory structures to be used for decoded data and allows for type checking
    and autocompletion in IDEs when writing programs that use those data structures.

    * Benefits of Binary encodings:
        * More compact than text encoding like XML, JSON, etc.
        * Schema is valid documentation as it is required to encode and decode, and must be up to date for it to work correctly.
        * Storing schemas allows for forward and backward compatibility.
        * For statically typed programming languages, the ability to generate code from the schema is very useful.
        * Much simpler than text encodings.
        * Schema evolution allows for the same flexibility/schemaless/schema-on-read as JSON databases that contain the document data model.
