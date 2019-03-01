//Room: /d/dali/jinzhihe.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","金汁河畔");
        set("long", @LONG
這裡位處金汁河畔，原本建有一座地藏寺，如今寺院早廢。唯有
一座石刻經幢(jingzhuang)半埋土中。此幢為方錐狀，七層石雕。高
約丈五尺，基座為八角形的磐石，邊上刻有蓮花；層與層之間有界石。
即是本層之蓋檐，又是上層之基石。
LONG );
        set("item_desc", ([
           "jingzhuang" : "這是個稀世經幢，進去看看也不壞。\n",
        ]));
        set("objects", ([
           "/d/dali/npc/seng": 2,
                "/clone/npc/walker"  : 1,
        ]));
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "east"  : "/d/dali/yanchi1",
            "west"  : "/d/dali/xiaojing",
            "enter" : "/d/dali/jingzhuang1",
        ]));
	set("coor/x", -19090);
	set("coor/y", -6870);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}