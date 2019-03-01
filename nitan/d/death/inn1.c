#include <ansi.h>
#include <command.h> 
inherit ROOM;
 
int do_stuff(object ob);
 
void create()
{
        set("short", HIB "【小店】" NOR);
        set("long", HIB @LONG

                      小                店  

    你一進來就發現屋裡異常的溫暖，牆角壁爐裡微弱的火光將你的影
子投射在對面的牆上。幾個人影圍在爐旁不知在討論些什麼。屋內有幾
張木桌、椅，牆上掛了幾幅字畫，一切看來非常的詳和寧靜，你幾乎忘
了自己身在何處。


LONG NOR );
        set("exits", ([
                 "east" : "/d/death/road1",
        ]));
 
        set("objects", ([
                __DIR__"npc/ghost": 1,
        ]) );

        set("item_desc", ([
                "shadows" : @SHADOWS
從你站的位置很難辨別出那幾個人的容貌, 四個披著黑鬥蓬的人斜靠在壁
爐邊的角落, 偶爾傳來其中幾人說話的聲音, 不過從這個距離你無法聽到
他們討論的內容. 當你還在考慮要不要靠過去一點時, 其中一人回頭看了
你一眼, 你愣住了... 那人... 那人......... 居然長得跟你一模一樣!
SHADOWS
        ]) );
        
        set("no_fight", 1);
        set("no_sleep_room", 1);

        setup();
}

void init()
{
        add_action("redirect_ask", "ask");
}
 
int redirect_ask(string str)
{
        object ob;
        string name, tmp1, tmp2;
        
        ob = this_player();
        name=query("id", ob);
        
        // if (! str || ! ob->is_ghost()) return 0;
        if (!str ) return 0;
        if (sscanf(str,"%s about %s",tmp1, tmp2) == 2) {
                if (tmp1 == name && tmp2 =="回家") 
                        return do_stuff(ob);
                        else return 0;
        }
        else return 0;
        return 0;
}
 
int do_stuff(object ob)
{
        int i;
        object *inv;

        write("你走上前去, 低聲的向那個長得跟你一樣的人詢問回家的事.\n");
        tell_room(environment(ob),query("name", ob)+
                "往壁爐那走去, 和一群黑影般的人不知說了些什麼.\n",
                ({this_object(), ob}));
        tell_room(environment(ob),
                "一眨眼的功夫"+query("name", ob)+"竟然不見了.\n",
                ({this_object(), ob}));
        write("那人一句話也不說就往你這邊撞過來, 你眼前一陣黑....\n");
        ob->reincarnate();
        if (! wizardp(ob))
        {
                inv = all_inventory(ob);
                for (i = 0; i < sizeof(inv); i++)
                        DROP_CMD->do_drop(ob, inv[i]);
        }

        ob->move("/d/city/wumiao");
        message("vision",
                "你忽然發現前面多了一個人影，不過那人影又好像已經在那裡\n"+
                "很久了，只是你一直沒發覺。\n", environment(ob), ob);
        return 1;
}
