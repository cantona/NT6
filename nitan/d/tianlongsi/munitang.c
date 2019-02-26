inherit ROOM;

void create()
{
        set("short", "牟尼堂");
        set("long", @LONG
這是高僧們的靜修之處。整堂全以松木製成，板門木柱，木料均
不去皮，天然質樸，和一路行來金碧輝煌的殿堂截然不同。
LONG );
        set("exits", ([
                "north": __DIR__"banruotai",
        ]));
        set("objects",([
                CLASS_D("tianlongsi") + "/kurong"   : 1,
                CLASS_D("tianlongsi") + "/benguan"  : 1,
                CLASS_D("tianlongsi") + "/benxiang" : 1,
                CLASS_D("tianlongsi") + "/bencan"   : 1,
                CLASS_D("tianlongsi") + "/benyin"   : 1,
        ]));
        setup();
}

void init()
{
        add_action("do_quit", "quit");
        add_action("do_quit", "exit");
}

string long()
{
        if (mapp(query("exits")))
                return query("long");

        return query("long") + "    現在室內劍氣縱橫，你來"
               "我往，殺個不停。\n";
}

int do_quit()
{
        object me;

        me = this_player();
        if (! mapp(query("exits")))
        {
                write("現在沒有出路，你無法離開。\n");
                return 1;
        }

        return 0;
}