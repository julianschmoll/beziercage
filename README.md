# jSmear Deformer

Maya Smear deformer.

## Building

### Building on Windows

1. Clone the repository
2. Run `build <MayaVersion>` in root of repository

### Building on other Systems

1. Clone the repository
2. Run `./build.sh <MayaVersion>`

## Testing

After Building it is recommended to run automated unittests by either running `test <MayaVersion>` on Windows or `./test.sh <MayaVersion>` on other systems. The unittests use mayapy being shipped with Maya. If maya is installed in the default location it will be picked automatically, otherwise it can be specified by adding `--mayapy /path/to/mayapy` to test command.

## License 

Distributed under the MIT License. See [LICENSE](./LICENSE) for more information.
