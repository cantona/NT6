inherit ROOM;
#include <ansi.h>

void create()
{
        set("short",HIB"墓地"NOR);
        set("long",@LONG
走到這裏越發感到荒涼，黃葉隨風亂舞，四處瀰漫着朽木腐爛的氣味。沒
膝的雜草中有一座土墳，墓碑(bei) 上落滿了塵土，不仔細看，很難辯出上面
寫些什麼。墓前並無紙灰，看起來好久沒有人來祭拜了。
LONG
        );
        set("no_fight", 1);
        set("no_get_from", 1);
        set("no_sleep_room", 1);
        set("dao_count",1);
        set("exits", ([
               "south" : __DIR__"shulin6",
        ]) );
        set("quest",1);

        set("objects",([
            __DIR__"npc/hu-fei" : 1,
        ]));

        set("item_desc", ([
                "bei"||"墓碑"||"碑":@LONG
             ________
            /        \
           /          \
          |        遼  |
          |            |
          |        東  |
          |     胡     |
          |     一 大  |
          |     刀     |
          |     夫 俠  |
          | 苗  婦     |
          | 人         |
          | 鳳  之     |
          | 立         |
          |     墓     |
          |            |
LONG
        ]) );

        set("coor/x",70);
        set("coor/y",80);
        set("coor/z",0);
        setup();
}

void init()
{
        add_action("do_wa", "wa");
}

int do_wa(string arg)
{
        object dao, me, ob;
        me = this_player();

        if( ! arg || arg != "di")
                return notify_fail("你要挖什麼？\n");

        if( ob = present("hu fei",environment(me)) &&!me->query("quest/雪山飛狐/復仇篇/over")) {
//              message_vision("$N用一種異樣的眼神看着$n。\n", ob,me);
                return notify_fail(CYN"胡斐喝道：休要打擾我爹孃的清靜！\n"NOR"你不敢再有動作！\n");
        }

        if ((int)me->query("jingli") < 500)
                return notify_fail("你的精力不夠做這件事！\n");

        if(random(10)!=6) {
                me->add("jingli",-200);
                return notify_fail("你看準了墓後三尺之處，運勁於指，伸手挖土。\n");
        }

        dao = new(__DIR__"obj/lengyue-dao");

        if(!clonep(dao)){
                tell_room(environment(me), me->name() + "挖了半天，只弄了一手泥。\n", ({ me }));
                return notify_fail("你挖了半天，只弄了一手泥。\n");
        }

        if(clonep(dao) && dao->violate_unique()){
                destruct(dao);
                tell_room(environment(me), me->name() + "挖了半天，只弄了一手泥。\n", ({ me }));
                return notify_fail("你挖了半天，只弄了一手泥。\n");
        }
        message_vision("挖地三尺，$N感到雙手手指同時碰到一件冰冷堅硬之物，再向兩旁摸索，是一柄帶鞘的單刀。\n"+
                       "$N抓住刀柄輕輕把單刀從土中抽出，刀刃抽出寸許，毫無生鏽。\n",me);
        me->add("jingli", -500);
        dao->move(me);
        return 1;
}
