// Room: /binghuo/shulin3.c
// Date: Oct.28 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "大樹林");
        set("long", @LONG
這裏綠樹成蔭。奇花異卉，長青闊葉，漫山遍野。在這極北之處，
居然有此林木，看來是拜火山之賜了。偶爾驚起一些叫不出名目的大
鳥小獸，也不避人。
LONG );
        set("outdoors", "binghuo");
        set("exits", ([
                "southwest" : __DIR__"shulin2",
                "south"     : __DIR__"pingyuan1",
                "northeast" : __DIR__"yuanye1",
                "northwest" : __DIR__"shanlu1",
        ]));
        set("objects", ([
                "/d/guanwai/npc/buck": 1,
                "/d/guanwai/npc/doe": 1,
        ]));
        setup();
}

int valid_leave (object who, string dir)
{
        if(dir != "northwest")
        {
                return ::valid_leave(who, dir);
        }
        else
        {
                if( query_temp("binghuo", who)>10 )
                {
                        return 1;
                }
                else
                {
                        addn_temp("binghuo", 1, who);
                        who->start_busy(2);
                        return notify_fail("你向西北踉蹌走去，可是好像方向不對，摸了半天，又回到了原地。\n");
                }
        }
}

void fall_down (object who, object where)
{
        who->move(where);
        this_player()->unconcious();
}
void fall_down1 (object who, object where)
{
        this_player()->unconcious();
}
