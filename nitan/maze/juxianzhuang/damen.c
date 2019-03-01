// This program is a part of NT MudLIB

inherit  ROOM;

void create()
{
        set("short",  "遊府大門");
        set("long",  @LONG
遊氏雙雄身為一方豪富，卻不失武林中人的本色，宅邸之中的演
武場修葺得尤為廣闊，場中旌旗蔽空，檣帆林立，場邊的兵器架上擺
放著刀、槍、劍、戟、錘等十八般兵器，被家丁們擦拭得寒光閃閃。
遊氏雙雄嗜武成痴，時常邀請武林中的前輩耆宿、後起之秀來莊中比
試切磋。
LONG);
        set("outdoors", "luoyang");
        set("region", "luoyang");
        set("no_fight", 1);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "east"  :  "/d/luoyang/suishi2",
                "west"  :  __DIR__"dayuan",
        ]));
        set("objects",([
                __DIR__"npc/xu" : 1,
        ]));

        setup();
        //replace_program(ROOM);
}

int valid_leave(object me, string dir)
{
        object ob, room;

        if( me->query_temp("juxianzhuang_step") != 6 &&
            me->query_temp("juxianzhuang_step") != 13 )
                if( objectp(present("xu zhanglao", environment(me))) && dir == "west" )
                        return notify_fail("徐長老攔住你說：你來洛陽聚賢莊撒野？快走開！\n");

        if( me->query_temp("juxianzhuang_step") == 13 && dir == "west" )
        {
                int valid;

                valid = FUBEN_D->valid_enter(me, "juxianzhuang");
                if( valid >=1 )
                {
                        room = get_object("/f/juxianzhuang/"+me->query("id")+"/zhengting");
                        ob = new("/maze/juxianzhuang/npc/azhu");
                        ob->move(room);
                        ob = new("/maze/juxianzhuang/npc/qiaofeng2");
                        ob->move(room);
                        FUBEN_D->enter_fuben(me, "juxianzhuang");
                        return -1;
                }
                else
                        return notify_fail("你無法進入聚賢莊副本。\n");
        }

        return ::valid_leave(me, dir);
}
