// /d/gaoli/shanghang
// Room in 高麗
inherit ROOM;
void create()        
{
        set("short", "商行");
        set("long", @LONG
這是高麗最負勝名的商行--廣義隆，這個商行的貨物遠到碎葉。嶺
南域內外都有它的分店，據説這裏的老闆喜好收藏，藏品豐厚，其中有
不少稀奇古怪的奇珍異寶，只是誰也沒見過。
LONG
        );
set("exits", ([
               "north":__DIR__"baihu-1", 
        ]));
set("objects", ([
                "/d/gaoli/npc/cui" : 1,
        ]));

       setup();
        replace_program(ROOM);
}        
