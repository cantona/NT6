/* /std/room/danger_road.c
*
*  走夜路有可能遇到強盜,此為一個標準被劫的 road ,
*  每一條路上視此路的長短和偏僻程度可放置幾個這個
*  被劫的路,簡單繼承此物件即可 "inherit DANGER_ROAD",
*  不要繼承 ROOM , 其他就不用管了.
*  注意:如果您的房間裡用到了init() 函數,請在結尾處
*  加上 ::init().
*
*  by 發現號(Find) 10/98.
*/

#define TOU_MU                __DIR__"npc/qiangdao_t"
#define LOU_LOU                __DIR__"npc/qiangdao"

inherit ROOM;

void init()
{
        string day_night;
        int time,n;
        object obj,obj_1,obj_2,me = this_player();
        mapping exits;
        string *dir = ({});

        if(is_day() || !userp(me) || !living(me))
                return;
return;
        if( query_temp("init_qiangdao", me) )
                return;

        if ( sscanf( NATURE_D->day_or_night(),"%s %d",day_night,time) )
        {
                if( day_night == "night"
                && time > 60
                && !present("qiang dao",this_object())
                && !present("qiangdao leader",this_object())
                && !me->is_fighting()
                && random(100) < 15 )
                {
                        obj = new(TOU_MU);        // 頭目出場
                        obj->set_attribute(me);

                        n = 1+random(3);

                        if(n-1)
                        {
                                obj_1 = new(LOU_LOU);        //強盜甲出場
                                obj_1->set_leader(obj);
                                set("my_leader", obj, obj_1);
                                addn("tonghuo/", ({obj_1}), obj);
                                obj_1->set_attribute(me);

                                if(n-2)
                                {
                                        obj_2 = new(LOU_LOU);        // 強盜乙出場
                                        obj_2->set_leader(obj);
                                        set("my_leader", obj, obj_2);
                                        addn("tonghuo/", ({obj_2}), obj);
                                        obj_2->set_attribute(me);
                                }
                        }

                        if(!me || !environment(me))
                        {
                                destruct(obj);
                                if(obj_1) destruct(obj_1);
                                if(obj_2) destruct(obj_2);
                                return;
                        }

                        set_temp("init_qiangdao", 1, me);
                        exits=query("exits", environment(me));
                        if(mapp(exits))
                                dir = keys(exits);
                        obj->set_leader(me);

                        obj->move(environment(me));

                        message_vision("\n突然旁邊竄出"+chinese_number(n)+"條蒙面大漢朝著$N走了過來。\n",me);
                        message_vision("\n$N惡狠狠的對著$n喊道：打劫！拿出"+
                                chinese_number((query("age", me)/10)*10)+
                                "兩銀子算完事，要不讓你活不到天亮!\n\n",obj,me);
                        obj->ask_money();
                        if(sizeof(dir))
                                GUARD_CMD->main(obj,dir[0]);

                        if(obj_1)
                        {
                                obj_1->move(environment(me));
                                if(sizeof(dir) > 1)
                                        GUARD_CMD->main(obj_1,dir[1]);
                        }
                        if(obj_2)
                        {
                                obj_2->move(environment(me));
                                if(sizeof(dir) > 2)
                                        GUARD_CMD->main(obj_2,dir[2]);
                        }
                        return;
                }
        }
}