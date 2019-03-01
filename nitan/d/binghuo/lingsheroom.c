// Room: /binghuo/lingsheroom.c
// Date: Oct.28 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "山頂小屋");
        set("long", @LONG
這裡是金花婆婆在島上的居所。小屋是島上漫山遍野生長的青竹
搭就。海風吹響，很是涼爽。四壁小竹窗，盡收窗外婆娑樹影後的蘭
天、白雲、碧海和黃沙，主人把這收拾得極為清雅。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "out" : __DIR__"lingshetop",
        ]));
        set("objects", ([
                CLASS_D("mingjiao")+"/daiqisi": 1,
        ]));
        setup();
}
void init()
{
        object weapon, ob, me = this_player();
        mapping weapon_prop;
        string *apply, type;

        if(objectp(ob = present("dai yisi", environment(me))) && living(ob))
        {
                weapon = new(WEAPON_DIR"treasure/jinhua");
                if ( weapon->violate_unique() )
                {
                        destruct( weapon );
                }
                else
                {
                        if(!present("duoming jinhua", ob))
                        {
                                weapon->move(ob);
                                weapon_prop=query("weapon_prop", weapon);
                                apply = keys(weapon_prop);
                                for(int i = 0; i<sizeof(apply); i++)
                                        addn_temp("apply/"+apply[i], weapon_prop[apply[i]], ob);
                                set_temp("weapon", weapon, ob);
                                ob->reset_action();
                                set("equipped", "wielded", weapon);
                        }
                }
        }
}
