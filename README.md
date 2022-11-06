# ECV - Latinsquare

**:star2: Exact cover problem - Latin square application :star2:**

Graphic toy written in C++/Qt to solve the [**latin square problem**](https://en.wikipedia.org/wiki/Latin_square).

Under the hood, it uses the [**ECV library**](https://github.com/MericLuc/ecv) that implements [Donald Knuth's Algorithm X](https://arxiv.org/pdf/cs/0011047v1.pdf). 

![example](imgs/example.gif)

## How to build/install

_Dependencies_ : 
  - Qt5 (Qt5::Widgets package)
  - ecv (as a submodule)

Start by getting the sources :

```
[~/git] git clone https://github.com/MericLuc/ecv-latinsquare.git
[~/git] git submodule update --init --recursive
```

Then, the easiest way to build is to use it as a QtCreator project.

Otherwise, you can build from command-line using cmake and defining a bunch of Qt related variables.

It should be something like that (not garanteed) : 

```
[~/builds] cmake -S ${PATH_TO_PROJECT} -B ${PATH_TO_BUILD} -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=${PATH_TO_QT_INSTALL}
[~/builds] make
```

## Example usage

[**Play**](https://mericluc.github.io/ecv/latinsquare/app.html) in your browser using a [webassembly](https://webassembly.org/) compiled version.

_Rules_ : 
  - Hover a cell to select it.
  - Enter a number between 1 - N (N being the dimension of the grid) to mark the cell.
  - Enter '0' to remove a value from a cell.
  - For the rest, I think the UI buttons are self-explanatory 😁