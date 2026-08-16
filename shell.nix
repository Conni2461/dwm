with import <nixpkgs> {};
stdenv.mkDerivation {
  name = "dwm";
  nativeBuildInputs = [ pkg-config ];
  buildInputs = [
    libX11
    libXinerama
    libXft
  ];
}
