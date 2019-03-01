// Room: /binghuo/lingshegang.c
// Date: Oct.28 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "靈蛇島海港");
        set("long", @LONG
這是個樹木蔥翠的大島，島上奇峰挺拔，聳立著好幾座高山。島
東端山石直降入海，並無淺灘，往來船只近岸泊就。此時岸邊正好有
一艘大船(chuan)，可是奇怪的是主桅上居然沒有帆布。
LONG );
        set("outdoors", "lingshe");
        set("no_clean_up", 0);
        set("item_desc", ([
                "chuan" : "一艘三桅白帆海船。上船就可以出海。\n",
        ]));
        set("exits", ([
                "westup"  : __DIR__"lingsheroad4",
                "enter"   : __DIR__"northboat1",
        ]));
        setup();
        replace_program(ROOM);
}
