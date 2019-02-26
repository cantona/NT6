// Room: diecong2.c

inherit ROOM;

void create()
{
        set("short", "蝶叢");
        set("long", @LONG
你現在正站在一個蝶叢裏，嗯....這是一個蝶叢....滿是蝴蝶和花
草....還有那沁人心脾的花的芬芳....，茂密的花草遮蔽了道路，
使你連方向都弄不清楚，一個聲音在你的腦海中迴盪：
        “別出去了，就留在這人間仙境吧...........!!!!”
LONG
        );
        set("outdoors", "oldpine");
        
        setup();
}

void reset()
{
        ::reset();
        set("exits", ([ /* sizeof() == 4 */
          "south" : __DIR__"diecong" + (random(6)+1),
          "north" : __DIR__"diecong" + (random(6)+1),
          "west" : __DIR__"diecong" + (random(6)+1),
          "east" : __DIR__"diecong" + (random(6)+1),
          "southeast" : __DIR__"shanjiao",
        ]));
}

int valid_leave(object me, string dir)
{
        write("你實在弄不清楚方向....");
        switch(dir) {
                case "north":   write("北邊....北邊是哪裏呢？....");    break;
break;
                case "east":    write("東邊....東邊....");      break;
                case "south":   write("南邊....哪裏是南邊？....");      break;
break;
                case "west":    write("西邊....嗯....");        break;
                default:
                        write("該往哪裏走呢....");
        }
        write("就是這個方向吧。\n");
        return 1;
}
