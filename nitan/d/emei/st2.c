#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "深潭");
        set("long", @LONG
四周黑濛濛，什麼都看不清。潭水發着惡臭，偶爾還會觸及一兩
根不知是人是獸的枯骨，讓你全身直起雞皮疙瘩。你漂浮在水中，無
助至極。情急之下唯有四處張望。
LONG );
        set("no_sleep_room",1);
        set("objects", ([
                __DIR__"npc/frog" : 1,
        ]));
        set("no_clean_up", 0);
        setup();
}

void init()
{
            add_action("do_wang", "wang");
}

int do_wang()
{
            object ob = this_player();

            message_vision(HIC "\n$N" HIC "極目四望，發現還是有出路的，於"
                       "是求生試探之心大動。\n"NOR, ob);

            switch (random(4))
            {
        case 0 : set("exits/east", __DIR__"st1"); break;
        case 1 : set("exits/east", __DIR__"st2"); break;
        case 2 : set("exits/east", __DIR__"st1"); break;
        default: set("exits/east", __DIR__"st2");
        }
        switch (random(4))
        {
        case 0 : set("exits/west", __DIR__"st1"); break;
        case 1 : set("exits/west", __DIR__"st1"); break;
        case 2 : set("exits/west", __DIR__"st2"); break;
        default: set("exits/west", __DIR__"st2");
        }
        switch (random(4))
        {
        case 0 : set("exits/south", __DIR__"st2"); break;
        case 1 : set("exits/south", __DIR__"st2"); break;
        case 2 : set("exits/south", __DIR__"st1"); break;
        default: set("exits/south", __DIR__"st1");
        }
        switch (random(4))
        {
        case 0 : set("exits/north", __DIR__"ssyb"); break;
        case 1 : set("exits/north", __DIR__"st1"); break;
        case 2 : set("exits/north", __DIR__"st2"); break;
        default: set("exits/north", __DIR__"st1");
        }
        remove_call_out("close_out");
        call_out("close_out", 3);
        return 1;
}

void close_out()
{
            if (query("exits/east"))
                delete("exits/east");

            if (query("exits/west"))
                delete("exits/west");

            if (query("exits/south"))
                delete("exits/south");

            if (query("exits/north"))
                delete("exits/north");
}