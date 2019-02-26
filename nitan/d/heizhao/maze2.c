// Code of ShenZhou
// Room: /d/heizhao/maze2.c
// AceP

inherit ROOM;

int do_out();

void create()
{
        set("short", "迷宮樹林");
        set("long", @LONG
這是迷宮中的一個路口，但見四下黑森森的都是樹木，腳下小路
東盤西曲，密林中難辨方向，舉步踏到的盡是矮樹雜草，荊棘鈎刺到
小腿，劃得你鮮血淋淋。一個小木樁上釘了五個木牌，分別指向五條
小路，並標明『金，木，水，火，土』。北邊樹木稀少些，看來可以
是走出去(out)的方向。
LONG );
        set("exits", ([
                "金" : __FILE__,
                "木" : __FILE__,
                "水" : __FILE__,
                "火" : __FILE__,
                "土" : __FILE__,
                ]));

        set("invalid_startroom", 1);
        set("cost", 3);
        set("outdoors", "heizhao");
        set("coor/x", -38000);
        set("coor/y", -71020);
        set("coor/z", 0);
        setup();
}

void init()
{
        object me;
        me=this_player();

        if (me->query_skill("dodge",1)<100 && random(10)==1) {
                message_vision("$N一個不小心，在樹叢上一拌，“咕嘟”一下摔進了荊棘叢。\n", me);
                addn("qi", -100, me);
                addn("eff_qi", -100, me);
                message_vision("$N掙扎了半天，從荊棘叢裏爬了出來，渾身扎滿了刺，痛苦難當。\n", me);
        }
        add_action("do_out", "out");
}

int valid_leave(object me, string dir)
{
        int mazepath;
        string walked,mpath;

        mazepath=query_temp("mazepath", me);

        mpath=sprintf("%d",mazepath);
        tell_object(me, "密碼："+mpath+"\n");

        walked=sprintf("%d%d%d%d%d",(query_temp("mark/maze金", me)-1),(query_temp("mark/maze木", me)-1),(query_temp("mark/maze水", me)-1),(query_temp("mark/maze火", me)-1),(query_temp("mark/maze土", me)-1));
        tell_object(me, "走過："+walked+"\n");

        addn("qi", -10, me);

        if (walked==mpath) {
                tell_object(me,"你苦思冥想，精掐細算，終於找到了破此迷宮之道。只三轉兩轉，便走了出去。\n");
                set("exits/"+dir, __DIR__"shanlu5"); 
                remove_call_out("closing");
                call_out("closing",1,dir);
                return 1;
        }
                
        if (dir=="金")
                addn_temp("mark/maze金", 1, me);
        if (dir=="木")
                addn_temp("mark/maze木", 1, me);
        if (dir=="水")
                addn_temp("mark/maze水", 1, me);
        if (dir=="火")
                addn_temp("mark/maze火", 1, me);
        if (dir=="土")
                addn_temp("mark/maze土", 1, me);
        return ::valid_leave(me, dir);
}

void closing(string dir)
{
        set("exits/"+dir, __FILE__);
        return;
}

int do_out()
{
        object me;
        me=this_player();

        tell_object(me, "你苦思冥想，左轉右看了許久，覺得沒有什麼辦法找到路，只好從原路退了回去。\n");
        set_temp("mark/maze金", 1, me);
        set_temp("mark/maze木", 1, me);
        set_temp("mark/maze水", 1, me);
        set_temp("mark/maze火", 1, me);
        set_temp("mark/maze土", 1, me);
        delete_temp("mazepath", me);
        me->move(__DIR__"maze1");
        return 1;
}
