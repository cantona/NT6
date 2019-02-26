// Room: /d/shaolin/fzlou1.c
// Date: YZC 96/01/19
// Date: cleansword 96/02/24

inherit ROOM;

void create()
{
        set("short", "茶室");
        set("long", @LONG
這裏是方丈待客的地方，靠牆左右兩側擺着一溜太師椅。北面牆
上掛了一付對聯。牆角一幾，放着幾個茶壺。有個茶壺壺身上題了『
碧螺春』三個篆字，壺嘴熱氣騰騰，似乎是剛沏的新茶。往北是方丈
室。
LONG );
        set("exits", ([
                "north" : __DIR__"fzlou2",
                "down" : __DIR__"fzlou",
        ]));
        set("objects",([
                CLASS_D("shaolin") + "/qing-le" : 1,
        ]));
//        set("no_clean_up", 0);
        setup();
}

int valid_leave(object me, string dir)
{
        int skill;

        skill = me->query_skill("buddhism", 1);
        if (!wizardp(me) && skill < 30)
        {
                if (dir == "north" )
                {
                        return notify_fail("你資格不夠，不能進入方丈室。\n");
                }
        }
        return ::valid_leave(me, dir);
}
