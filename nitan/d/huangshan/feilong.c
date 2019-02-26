// Room: /d/huangshan/feilong.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "飛龍峯");
        set("long", @LONG
這裏很少有遊人前來，因此山勢險惡，且無什麼絕妙的景色，但是
武林人士倒喜歡來此探幽，更曾有高人隱居於此，所以後來者更是絡繹
不絕，期待能夠得到那傳説中的祕寶。可是山頂怪石林立，雜草叢生，
絲毫不見有人的跡象，但是誰也不肯放棄希望，都要搜一搜。
LONG
        );
        set("exits", ([ 
                "southwest" : __DIR__"qingliang",
        ]));
        set("outdoors", "huangshan");
        set("coor/x", -585);
        set("coor/y", -990);
        set("coor/z", -10);
        setup();
}
void init()
{
        add_action("do_search", "搜");
        add_action("do_search", "search");
        add_action("do_search", "sou");
}
int do_search()
{
        string *names = ({"髒髒的","劃破的","撕成條的","沾滿污泥的"});
        object clo, me = this_player();

        clo = new("/clone/cloth/cloth");
        set("name", names[random(sizeof(names))]+"布衣", clo);
        message_vision("$N在這怪石林立，雜草叢生的山頂不停地搜尋着．．\n",me);
        if(!me->is_busy())
        {
                tell_object(me,"你發現了一件"+clo->name()+"。\n");
                clo->move(me);
        }
        me->start_busy(4);
        return 1;
}