# Silnik2D
najnowsza wersja rayliba:
https://github.com/raysan5/raylib/releases/tag/6.2
https://github.com/raysan5/raylib/releases/download/6.2/raylib-6.2_win64_msvc16.zip

odpakuj w dowolne miejsce

skonfigurowanie rayliba z naszym projektem w visual studio:
w Solution Explorer kliknij prawym przyciskiem myszy "Silnik2D" -> na samym dole pojawi się pole "Properties"
w sekcji C/C++ -> General -> Additional Include Directories - wklej CAŁĄ ścieżkę do folderu include w folderze rayliba, u mnie jest tak:
C:\Users\smoka\OneDrive\Desktop\raylib-5.5_win64_msvc16\raylib-5.5_win64_msvc16\include

potem w sekcji Linker -> General -> Additional Library Directories - wklej całą ścieżkę do folderu lib w raylibie, u mnie jest:
C:\Users\smoka\OneDrive\Desktop\raylib-5.5_win64_msvc16\raylib-5.5_win64_msvc16\lib

i na koniec w sekcji Linker -> Input -> Additional Dependencies - jeśli masz tam cokolwiek wpisane to NIE usuwaj, kliknij w pole, z boku po prawej pojawi się 
kwadracik ze strzałką w dół, kliknij ją -> <Edit...> -> powinno być tak:
raylib.lib;
winmm.lib;
$(CoreLibraryDependencies);%(AdditionalDependencies)

kliknij OK i spróbuj odpalić projekt skrótem klawiszowym ctrl + F5
