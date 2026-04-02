# BarcodeKit

A C++ barcode encoding library with an Objective-C++ view controller for macOS (Cocoa). It encodes data into barcode symbol sequences that can be rendered in a Cocoa view.

## Supported Symbologies

| Symbology | Class |
|---|---|
| Codabar | `Codabar` |
| Code 39 | `Code39` |
| Code 128 | `Code128` |
| Code 16K | `Code16k` |
| Interleaved 2 of 5 | `Interleaved2of5` |
| EAN-13 | `EAN13` |
| EAN-8 | `EAN8` |
| UPC-A | `UPCA` |
| UPC-E | `UPCE` |

## Requirements

- macOS with Xcode command-line tools installed
- A C++11-capable compiler (clang++ ships with Xcode)
- The [rapidxml](http://rapidxml.sourceforge.net) header library (included in `BarcodeKit/rapidxml/`)

## Building

There is no Xcode project included. You can compile the command-line test harness directly with clang++:

```bash
cd BarcodeKit/BarcodeKit

clang++ -std=c++11 -o BarcodeKit \
    main.cpp \
    Symbol.cpp \
    BaseBarcode.cpp \
    BaseEANUPC.cpp \
    Base128.cpp \
    Codabar.cpp \
    Code39.cpp \
    Code128.cpp \
    Code16k.cpp \
    Interleaved2of5.cpp \
    EAN8.cpp \
    EAN13.cpp \
    UPCA.cpp \
    UPCE.cpp
```

## Running

```bash
./BarcodeKit
```

The default `main.cpp` encodes the EAN-8 value `9016280` and prints the resulting symbol data to stdout. Change the barcode type and input string in `main.cpp` to test other symbologies.

## Using the Library in Your Own Project

1. Copy the `BarcodeKit/` source files into your Xcode project.
2. For a Cocoa app, add `RSBarcodeViewController.h` / `RSBarcodeViewController.mm` to your target.
3. Instantiate a view controller with a barcode type and data string:

```objc
#import "RSBarcodeViewController.h"

RSBarcodeViewController *vc = [[RSBarcodeViewController alloc]
    initWithType:kRSEAN13
         andData:@"5901234123457"
      atPosition:NSMakeRect(50, 50, 300, 100)];
```

Available type constants: `kRSCodabar`, `kRSCode39`, `kRSInterleaved`, `kRSCode128`, `kRSEAN13`, `kRSEAN8`, `kRSUPCA`, `kRSUPCE`.

## Project Structure

```
BarcodeKit/
├── BaseBarcode.{h,cpp}         # Abstract base class
├── BaseEANUPC.{h,cpp}          # Shared EAN/UPC logic
├── Base128.{h,cpp}             # Shared Code 128/16K logic
├── Symbol.{h,cpp}              # Barcode symbol model
├── RSSymbol.{h,mm}             # Objective-C symbol wrapper
├── RSBarcodeViewController.{h,mm}  # Cocoa view controller
├── [Symbology].{h,cpp}         # One file pair per symbology
├── *.xml                       # Encoding tables (parsed via rapidxml)
└── rapidxml/                   # rapidxml header-only XML library
```

## License

Copyright © 2012 Cocoadelica. All rights reserved.
