inherit ROOM;  
#include <ansi.h> 
void create() 
{ 
        set("short", "精靈界");
        set("long",
HIG "這裡紫霓朦朧，瑞氣繚繞，虛空中有一幅詩卷：\n" NOR
HIW "第一個封印放樹巔，風精靈從此不再飛翔。\n"
    "第二個封印落水間，漣漪和浪花便斂起了鋒芒。\n"
    "第三個封印封鎖山巖，大地的歌聲轉為嗚嚥。\n"
    "第四個封印驅逐雷電，世間只剩下冰冷的火燄。\n"
    "第五個封印啊天空知道，太陽的光芒遠離了絕頂上神奇的瓊草。\n"
    "第六個封印也很清晰，月光在墓園裡不安地嬉戲。\n" 
    "可是第七個封印啊，我怎麼想也想不起。第七個封印啊我一生\n"
    "的靈契，我究竟把它忘在哪裡？\n" NOR
HIG "一個清靈美麗的女孩站在詩卷下，仿佛等待著什麼。\n" NOR
);
        set("exits", ([ 
   "south" : __DIR__"spirit1",
 ]));
        set("objects", ([ 
           "/quest/tulong/npc/leader" : 1,
]));
        set("no_clean_up", 0);

        set("no_magic", 1);
        setup();
        replace_program(ROOM);
}
