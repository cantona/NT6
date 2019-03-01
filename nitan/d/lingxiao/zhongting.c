inherit ROOM;
#include <ansi.h> 

void create()
{
        set("short", "中庭");
        set("long", @LONG 
這裡是凌霄城的中庭，左右都是凌霄弟子的住所。白自在對
諸弟子要求嚴厲。所以凌霄弟子平時除練劍習武外，無事之時往
往便在房中研讀劍經拳譜，不敢稍有懈怠。 
LONG);
        set("outdoors", "lingxiao");
        set("exits", ([
                    "west"  : __DIR__"zoulang1",
                    "north" : __DIR__"houyuan1",  
                    "south" : __DIR__"qianyuan", 
                    "east"  : __DIR__"zoulang2",
        ]));        
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);

}
