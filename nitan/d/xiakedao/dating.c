//ROOM /d/xiakedao/dating.c

inherit ROOM;

int do_push(string arg);
void create()
{
        set("short", "大廳");
        set("long", @LONG
這是『俠客島』的大廳，四周點滿了牛油蠟燭，南面放著一個
大屏風。洞內擺著一百來張桌子，賓客正絡繹進來，數百名黃衣漢
子穿索般來去，引導賓客入座。
LONG );
//        set("valid_startroom",1);
        set("no_fight","1");
        set("item_desc",([
                "pingfeng" : "這是一個用玉石作的屏風，非常漂亮，也許你能用手把它推(push)開。\n",
        ]));
        set("exits", ([
                "north" : __DIR__"shidong5",
                "east"  : __DIR__"shufang",
                "west"  : __DIR__"wuqiku",
        ]));
        set("objects",([
                __DIR__"npc/dizi" : 4,
        ]));
        set("coor/x", -3080);
        set("coor/y", -22110);
        set("coor/z", 0);
        setup();
        "/clone/board/xiake_b"->foo();
}

void init()
{
        add_action("do_push","push");
}

int do_push(string arg)
{
        object *inv,me=this_player();
        int n, i;
        n=query("neili", me);
        inv = all_inventory(me);
        for(i=sizeof(inv)-1; i>=0; i--)
        {
                if( (query("id", inv[i]) == "pai1") && 
                    (query_temp("own", inv[i]) != query("id", me)) )
                    return notify_fail("俠客島弟子說道：這位" +
                      RANK_D->query_respect(me) + "好象不是俠客島的客人吧？\n");
                if( (query("id", inv[i]) == "pai2") && 
                    (query_temp("own", inv[i]) != query("id", me)) )
                    return notify_fail("俠客島弟子說道：這位" +
                      RANK_D->query_respect(me) + "好象不是俠客島的客人吧？\n");
        }
        if( !arg || arg!="pingfeng")
        {
                write("你要推什麼呀。\n");
                return 1;
        }
        message_vision("$N在屏風前站定，深吸一口氣，兩手緊握住屏風。\n", me);
        if (n >=100)
        {
                message_vision("$N丹田一運氣，猛的一推，只見屏風之後，露出一條長長的甬道。\n", me);
                set("exits/south", __DIR__"yongdao3");
                set("neili", n-100, me);
                remove_call_out("close");
                call_out("close",5, this_object());
        }
        else
        {
                message_vision("$N丹田一運氣，猛的一推，屏風卻絲毫沒動。\n", me);
                set("neili", 0, me);
        }
        return 1;
}
void close(object room)
{
        message("visoin", "屏風自動又合上了。\n", room);
        delete("exits/south", room);
}