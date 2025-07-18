# optional: upgrade to clang-20
wget https://apt.llvm.org/llvm.sh
chmod +x llvm.sh
sudo ./llvm.sh 20      # installs clang-20, clang-tidy-20, clang-format-20
sudo update-alternatives --install /usr/bin/cc  cc  /usr/bin/clang-20   100
sudo update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++-20 100
