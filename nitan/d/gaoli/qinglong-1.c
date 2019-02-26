// /d/gaoli/zhuquedajie2
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "飛鳳大街");
        set("long", @LONG
你走在一條寬闊的石板大街上。東面就是皇城御道了，南邊是兵營
的大門，裏面不時傳來吶喊的聲音。北邊是一個馬房，這裏可以聽到馬
叫的聲音，非常熱鬧。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "west" : __DIR__"qinglong-2",
                "east" : __DIR__"yudao4",
                "north":__DIR__"mafang",
                "south":__DIR__"bingyingdamen",    
        ]));
      set("objects",([
         __DIR__"npc/xiake":1,
         ]));
       setup();
        replace_program(ROOM);
}        
