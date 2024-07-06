pkgname=numguesser++
pkgver=1.4
pkgrel=1
pkgdesc="A random number guessing game written in C++"
arch=('x86_64')
url="https://github.com/Xatra1/numguesser-plus-plus"
pkgdir=pkg
license=('GPL3')
makedepends=('gcc' 'git')
source=(
    "https://raw.githubusercontent.com/Xatra1/numguesser-plus-plus/main/src/main.cc",
    "https://github.com/Xatra1/numguesser-plus-plus/releases/download/${pkgver}/numguesser++.1.gz",
    "https://github.com/Xatra1/numguesser-plus-plus/raw/main/LICENSE"
)
sha256sums=(
    'SKIP',
    'SKIP',
    'SKIP'
)
package() {
    c++ -o numguesser++ src/numguesser++.cc
    install -Dm755 numguesser++ "${pkgdir}/usr/games/numguesser++"
    install -Dm755 numguesser++ "${pkgdir}/usr/games/ng++"
    install -Dm644 numguesser++.1.gz "${pkgdir}/usr/share/man/man1/numguesser++.1"
    install -Dm644 LICENSE "${pkgdir}/usr/share/licenses/numguesser++/LICENSE"
}
