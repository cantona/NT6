// Room: chaopath2.c 朝陽峯小路
//Date: Oct. 2 1997 by Venus
inherit ROOM;

void create()
{
      set("short","朝陽峯小路");
        set("long", @LONG
這裏是朝陽峯小路，山勢陡峭，兩邊下臨深谷，一不小心都會掉
了下去。東面有一條小路，長草沒徑，小路順着山脊一路宛延而下至
華山後山裏。此處是華山前輩避世之處，輕易見不得人跡。就連華山
弟子若是不得傳招，也不能來此。北面的幾棟小屋，便是華山前輩的
居所。
LONG );
      set("outdoors", "huashan");
      set("exits",([ /* sizeof() == 1 */
          "southwest": __DIR__"chaopath1",
          "eastup"   : __DIR__"chaoyang",
          "westup"   : __DIR__"ziqitai",
          "northup"    : __DIR__"hsxiaowu",
      ]));
      set("objects", ([
          __DIR__"npc/shi-daizi" : 1,
      ]));
      setup();
}

void init()
{
        object me = this_player();
        if( query_temp("xunshan", me))set_temp("xunshan/chaoyang", 1, me);
        return;
}

int valid_leave(object me, string dir)
{
        if (dir != "northup"  ||
            ! objectp(present("shi daizi", environment(me))) ||
            (query("family/master_id", me) == "gaolaozhe") || 
            (query("family/master_id", me) == "ailaozhe") )
                return ::valid_leave(me, dir);

        if( query("family/family_name", me) != "華山派" )
        {
                message_vision("施戴子伸手攔住$N，道：抱歉，上面是兩位"
                               "長老清修之處，這位" + RANK_D->query_respect(me) +
                               "請止步！\n", me);
                return notify_fail("看來施戴子不會讓你過去。\n");
        }

        if( query("combat_exp", me)<100000 )
        {
                message_vision("施戴子伸手攔住$N，道：止步！上面是兩位"
                               "長老清修之處，你雖然是本派弟子，但是學"
                               "藝不精，不能拜見！\n", me);
                return notify_fail("看來施戴子不會讓你過去。\n");
        }

        return ::valid_leave(me, dir);
}