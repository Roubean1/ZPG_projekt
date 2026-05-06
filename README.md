# ZPG projekt

Semestrální projekt do ZPG vytvořený v C++ a OpenGL. Projekt obsahuje několik 3D scén, práci s kamerou, světly, shadery, texturami, modely a jednoduchými animacemi.

## Požadavky

- Visual Studio 2022
- Windows 10/11
- Platforma `x64`

Potřebné knihovny jsou přiložené přímo v projektu:

- GLEW
- GLFW
- GLM
- stb
- tinyobjloader

## Spuštění

1. Otevřete soubor `zpg_tok_novy.sln` ve Visual Studiu 2022.
2. V horní liště zvolte konfiguraci `Debug` a platformu `x64`.
3. Projekt sestavte pomocí `Build > Build Solution` nebo klávesovou zkratkou `Ctrl+Shift+B`.
4. Spusťte projekt pomocí `Local Windows Debugger` nebo klávesou `F5`.

Po úspěšném spuštění se otevře OpenGL okno s aplikací.

## Ovládání

- `W`, `A`, `S`, `D` - pohyb kamery
- pravé tlačítko myši + pohyb myší - rozhlížení kamerou
- `1` až `6` - přepínání scén
- levé tlačítko myši - výběr objektu / práce s objekty podle aktuální scény
- `F` - zapnutí/vypnutí reflektoru ve scénách, kde je dostupný
- `Delete` - smazání vybraného objektu
- `M` - přesun vybraného objektu
- `B` - zapnutí/vypnutí kreslení spline bodů
- `N` - spuštění pohybu po spline
- `C` - vymazání spline bodů
- `Esc` - zrušení aktuální akce nebo ukončení aplikace

## Scény

Projekt obsahuje tyto scény:

- Triangle scene
- Spheres scene
- Forest scene
- Solar system scene
- Meteor scene
- Race track scene

Scény se přepínají klávesami `1` až `6`.

## Struktura projektu

- `zpg_tok_novy.sln` - solution soubor pro Visual Studio 2022
- `zpg_tok_novy/` - zdrojové soubory projektu
- `zpg_tok_novy/assets/` - 3D modely, textury a další assety
- `zpg_tok_novy/shaders/` a `zpg_tok_novy/ShaderSource/` - shader soubory
- `zpg_tok_novy/Libraries/` - přiložené externí knihovny
- `zpg_tok_novy/Models/` - hlavičkové soubory s modely

## Poznámky

Projekt je připravený hlavně pro spuštění přes Visual Studio 2022. Stačí otevřít `.sln` soubor, zkompilovat řešení a spustit aplikaci.
