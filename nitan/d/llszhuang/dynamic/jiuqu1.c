inherit ROOM;
void create()
{
        set("short", "七曲九回廊");
        set("long",
"這裡是七、八十道長廊，相互接連，連綿不絕，直是無窮無盡。每個\n"
"長廊轉彎處都有一盞宛如鬼火般搖晃不定的黃燈。廊邊的潭水在燈光照射\n"
"下發出墨綠的異光。\n"
);
        set("no_magic", "1");
        setup();
}

int valid_leave(object me, string dir)
{
        object killer;

        if( random(query("kar", me))<20 && 
            ! objectp(present("figure", environment(me)))) 
        {
                killer = new(__DIR__"npc/killer");
                NPC_D->set_from_me(killer, me, 100);
                message_vision(killer->name() + "大聲喝道：誰人敢擅闖柳綠山莊？！拿命來吧！\n", me);
                killer->move(environment(me));
                killer->set_leader(me);
                return notify_fail("只見突然從地板下竄出一人，攔住了你的去路。\n");
        }
        return ::valid_leave(me, dir);
}

