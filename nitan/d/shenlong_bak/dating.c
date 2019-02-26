// /d/shenlong/dating 大廳
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>
inherit ROOM;
string* npcs = ({
        __DIR__"npc/boy",
        __DIR__"npc/boy2",
        __DIR__"npc/boy3",
        __DIR__"npc/boy4",
        __DIR__"npc/girl",
});
string look_jia();

void create()
{
        set("short", "大廳");
        set("long", @LONG
你來到了一個大廳之中，這廳碩大無朋，足可容得下千人之眾，一
羣羣少男少女分五色站好，青、白、黑、黃四色的都是少年，穿紅的卻
是少女，背上各負短劍，每一隊約有百人。每個隊列之前都站着一個頭
目。大廳四周有很多出口。四周豎着一排兵器架(shelf)。
LONG
        );
        set("exits", ([
                "out"   : __DIR__"tingkou",
                "east"  : __DIR__"shibanlu",
                "north" : __DIR__"zoulang",
        ]));
        set("objects", ([
                npcs[random(sizeof(npcs))] : 1,
                npcs[random(sizeof(npcs))] : 1,
                __DIR__"npc/yunsumei": 1,
                CLASS_D("shenlong")+"/wugen": 1,
        ]));
        set("item_desc", ([
                "shelf": (: look_jia :),
        ]));
        set("weapon_count", 10);
        setup();
}

void init()
{
        add_action("do_get", "get");
}

int do_get(string arg)
{
        object weapon, me = this_player();
        string type;

        if(!arg) return 0;
        if( me->is_fighting() || me->is_busy() ) return 0;
        if( sscanf(arg, "%s from shelf", type) != 1) return 0;
        if( time()<query("sg/weapontime", me)+300 && !wizardp(me) )
        {
                tell_object(me, "你太貪心了，還是等一下再來吧。\n");
                return 1;
        }
        if(query("weapon_count") < 1)
        {
                tell_object(me, "兵器架空空如也，看來都給別人取光了吧。\n");
                return 1;
        }
        if( type != "armor" )
        {
                if( (int)me->query_skill(type, 1) < 1 )
                {
                        tell_object(me, "你不會用這種武器。\n");
                        return 1;
                }
        }
        switch(type)
        {
                case"sword":if( query("gender", me) == "無性" )
                                        weapon = new(WEAPON_DIR"treasure/zhen");
                                else weapon = new(WEAPON_DIR"sword/changjian");
                                break;
                case "blade":   weapon = new(WEAPON_DIR"blade/gangdao");
                                break;
                case "stick":   weapon = new(WEAPON_DIR"zhubang");
                                break;
                case "staff":   weapon = new(WEAPON_DIR"gangzhang");
                                break;
                case "hammer":   weapon = new(WEAPON_DIR"hammer/tongchui");
                                break;
                case "whip" :   weapon = new(WEAPON_DIR"changbian");
                                break;
                case "hook" :   weapon = new(WEAPON_DIR"hook");
                                break;
                case "armor":   weapon = new(ARMOR_DIR"tiejia");
                                break;
                default:        tell_object(me, "找不到"+type+"這種兵器。\n");
                                return 1;
        }
        if( weapon->move(me) )
        {
                message_vision("$N從兵器架上取下一"+query("unit", weapon)+weapon->name()+"。\n",me);
                set("sg/weapontime", time(), me);
        }
        else
        {
                destruct(weapon);
        }
        addn("weapon_count", -1);
        return 1;
}

string look_jia() 
{
        string msg;

        msg ="這是一個兵器架，十八般武器是應有盡有。\n";
        msg+="目前存放有劍(sword)，刀(blade)，鈎(hook)，棒(stick)，杖(staff)，錘(hammer)，鞭(whip)。還有一些鐵甲(armor)。\n";
        msg+= "請用指令“get 種類 from shelf”拿取你稱手的兵器或甲胄。\n";
        return msg;
}

/*
int valid_leave(object me, string dir)
{
        if (dir == "east" &&
                query("party/party_name", me) != HIY"神龍教"NOR && 
                present("wugen daozhang", environment(me)) &&
                living(present("wugen daozhang", environment(me))))
                        return notify_fail("無根道長喝道：後面是本教重地，這位" + RANK_D->query_respect(me) + "請止步。\n");
        else return ::valid_leave(me, dir);

}
*/
