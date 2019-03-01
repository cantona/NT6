inherit ROOM; 
 
#include <ansi.h>
void create() 
{ 
        set("short", "精靈界");
        set("long",
"[1;32m這裡是一個異世界，來到這裡，已經遠離了你的江湖。這裡\n"
"沒有恩怨，沒有紛爭。有的只是動聽的音樂，優美的風景。十四根玉石柱\n"
"子參天而立，看不到盡頭。玉柱間白雲繚繞，透過白雲，隱約能看到雕欄\n"
"畫棟，聽到絲竹笙歌，光彩流動，奇麗不可名狀。這裡沒有晝夜之分，只\n"
"有空氣中不時傳來縷縷清香，令人感到平靜安寧。\n"
);
        set("exits", ([ 
  "north" : __DIR__"spirit2",
]));
        set("no_clean_up", 0);

        set("no_magic", 1);
        setup();
        replace_program(ROOM);
}
