// regiser: entry.c
// by Doing

#include <ansi.h>
#include <login.h>
#include <command.h>

inherit ROOM;

int is_chat_room() { return 1; }

int do_choose(string arg);
int do_washto(string arg);
int do_born(string arg);

mapping born = ([
        "關外人氏" : "/d/guanwai/kedian",
        "燕趙人氏" : "/d/beijing/kedian",
        "齊魯人氏" : "/d/taishan/kedian",
        "秦晉人氏" : "/d/changan/kezhan",
        "蒙古人氏" : 0,
        "中原人氏" : "/d/nanyang/kedian1",
        "西域人氏" : "/d/xingxiu/kezhan",
        "荊州人氏" : "/d/jingzhou/kedian",
        "揚州人氏" : "/d/city/kedian",
        "蘇州人氏" : "/d/suzhou/kedian",
        "杭州人氏" : "/d/hangzhou/kedian",
        "福建人氏" : "/d/fuzhou/rongcheng",
        "巴蜀人氏" : "/d/chengdu/kedian",
        "雲南人氏" : "/d/dali/kedian",
        "黔中人氏" : 0,
        "兩廣人氏" : "/d/foshan/beidimiao",
        "歐陽世家" : ([ "born"      : "西域人氏",
                        "surname"   : "歐陽",
                        "startroom" : "/d/baituo/dating",
                     ]),
        "關外胡家" : ([ "born"      : "關外人氏",
                        "surname"   : "胡",
                        "startroom" : "/d/guanwai/xiaowu",
                     ]),
        "段氏皇族" : ([ "born"      : "大理人氏",
                        "surname"   : "段",
                        "startroom" : "/d/dali/wangfugate",
                     ]),
        "慕容世家" : ([ "born"      : "江南人氏",
                        "surname"   : "慕容",
                        "startroom" : "/d/yanziwu/cuixia",
                     ]),
        "唐門世家" : ([ "born"      : "巴蜀人氏",
                        "surname"   : "唐",
                        "startroom" : "/d/tangmen/kedian",
                     ]),
]);

void create()
{
        int i, k;
        string desc;
        string *position;

        set("short", HIR "生命之谷" NOR);
        set("long",
"混沌初分盤古開天地，迷霧、微風，天地初開，四周混沌，霧茫\n"
"茫一片，這裏就是子天醜地人寅出的生命之谷。\n"
"　　谷中有一個石頭砌成的池子，其中水清澈卻不見底，不知道它究\n"
"竟有多深，池子正上方懸掛着太極兩儀四象，不知有何奧妙？！\n"
);
        set("no_fight", 1);
        set("objects", ([
                __DIR__"npc/pangu" : 1,
        ]));

        // set("no_say", "盤古正在閉目沉思，你哪裏敢亂説話？\n");

/*
        set("item_desc", ([
                "paizi" : "投胎乃人生大事，切記不可草率！選好方向，就輸入born <地名>。\n"
        ]));

        desc = query("item_desc/paizi");
        position = keys(born);

        for (i = 0, k = 1; i < sizeof(position); i++)
        {
                if (! stringp(born[position[i]]))
                        continue;

                desc += sprintf("%2d. " HIW "%s" NOR "\n", k++, position[i]);
        }

        for (i = 0; i < sizeof(position); i++)
        {
                if (! mapp(born[position[i]]))
                        continue;

                desc += sprintf("%2d. " HIC "%s" NOR "\n", k++, position[i]);
        }
        set("item_desc/paizi", desc);
*/

        setup();
}

void init()
{
        add_action("do_choose", "choose");
        add_action("do_washto", "washto");
        add_action("do_born", "born");
}

int do_choose(string arg)
{
        object me;
        int n;

        if (! objectp(me = this_player()) ||
            ! userp(me))
                return 1;
        
        if (! arg || arg == "")
                n = 1;
        else
                sscanf(arg, "%d", n);

        if (n < 1 || n > 4)
        {
                write("您只能選擇(choose)系統所提供的這四種角色性格：\n"
                    HIC "1" NOR ".光明磊落  "
                    HIC "2" NOR ".狡黠多變  "
                    HIC "3" NOR ".心狠手辣  "
                    HIC "4" NOR ".陰險奸詐 ("
                    HIC "choose 1" NOR "-" HIC "4" NOR ")\n");
                return 1;
        }

        switch(n)
        {
        case 1:
                set("character", "光明磊落", me);
                break;
        case 2:
                set("character", "狡黠多變", me);
                break;
        case 3:
                set("character", "心狠手辣", me);
                break;
        case 4:
                set("character", "陰險奸詐", me);
                break;
        }
        
        write(HIC"你選擇了"NOR+HIM+query("character", me)+NOR+HIC"的性格，接下來你可以洗(washto)天賦了。\n"NOR,me);
        write(HIY "新手導師：戚長髮有洗天賦丹出售(一兩黃金)，可以重新設定天賦，所以你不用在這裏糾結而浪費時間。\n" NOR); 
        write("指令格式：washto <膂力> <悟性> <根骨> <身法>\n例    如：washto 20 20 20 20\n"); 
        return 1;
}
        
int do_wash(string arg)
{
        int i;
        int points;
        int tmpstr, tmpint, tmpcon, tmpdex;
        object me;
        mapping my;

        if (! objectp(me = this_player()) ||
            ! userp(me))
                return 1;

        if( !query("character", me) )
        {
                write(HIC "你還是先確定(choose)好你的角色性格再選天賦吧。\n" NOR, me);
                return 1;
        }
                
        write(HIC "你跳入生命池，頓時被一股激流捲了進去。\n" NOR, me);

        tmpstr = tmpint = tmpcon = tmpdex = 13;

        switch(query("type", me) )
        {
        case "猛士型":
                tmpstr = 20;
                break;

        case "智慧型":
                tmpint = 20;
                break;

        case "耐力型":
                tmpcon = 20;
                break;

        case "敏捷型":
                tmpdex = 20;
                break;

        default:
                break;
        }

        points = 80 - (tmpstr + tmpint + tmpcon + tmpdex);
        for (i = 0; i < points; i++) {
                switch (random(4)) {
                case 0: if (tmpstr < 30) tmpstr++; else i--; break;
                case 1: if (tmpint < 30) tmpint++; else i--; break;
                case 2: if (tmpcon < 30) tmpcon++; else i--; break;
                case 3: if (tmpdex < 30) tmpdex++; else i--; break;
                }
        }

        my = me->query_entire_dbase();

        my["str"] = tmpstr;
        my["int"] = tmpint;
        my["con"] = tmpcon;
        my["dex"] = tmpdex;
        my["kar"] = 10 + random(21);
        my["per"] = 10 + random(21);

        write(HIC "“啪”的一聲，你被濕漉漉的拋了出來。\n" NOR, me);
        write(sprintf(HIY "\n你這次獲得的四項先天天賦分別是：\n"
                          "膂力：【 " HIG "%d" HIY " 】 "
                          "悟性：【 " HIG "%d" HIY " 】 "
                          "根骨：【 " HIG "%d" HIY " 】 "
                          "身法：【 " HIG "%d" HIY " 】\n"
                          "如果你滿意，就去投胎(born)吧！\n\n" NOR,
                      tmpstr, tmpint, tmpcon, tmpdex));
        set_temp("washed", 1, me);

        return 1;
}

int do_washto(string arg) 
{ 
        int tmpstr, tmpint, tmpcon, tmpdex, dower; 
        object me; 
        mapping my; 
  
        if (! objectp(me = this_player()) ||
            ! userp(me))
                return 1;

        if( !query("character", me) )
        {
                write(HIC "你還是先確定(choose)好你的角色性格再選天賦吧。\n" NOR, me);
                return 1;
        }
        
        if (! arg || sscanf(arg, "%d %d %d %d", tmpstr, tmpint, tmpcon, tmpdex) != 4)
                return notify_fail("指令格式：washto <膂力> <悟性> <根骨> <身法>\n" +
                                   "例    如：washto 20 20 20 20\n"); 
  
        if (tmpstr > 30 || tmpstr < 13) 
                return notify_fail("你所選擇的膂力數值要求必須在13和30之間。\n"); 
        
        if (tmpint > 30 || tmpint < 13) 
                return notify_fail("你所選擇的悟性數值要求必須在13和30之間。\n"); 
                
        if (tmpcon > 30 || tmpcon < 13) 
                return notify_fail("你所選擇的根骨數值要求必須在13和30之間。\n"); 
                
        if (tmpdex > 30 || tmpdex < 13) 
                return notify_fail("你所選擇的身法數值要求必須在13和30之間。\n"); 

        if (tmpstr + tmpint + tmpcon + tmpdex > 80) 
                return notify_fail("你所選擇的天賦數值總和不能大於80。\n"); 
        
        dower = 80 - (tmpstr + tmpint + tmpcon + tmpdex);
      
        write(HIC "你跳入忘憂池，頓時被一股激流捲了進去。\n" NOR, me); 
        my = me->query_entire_dbase(); 
  
        my["str"] = tmpstr; 
        my["int"] = tmpint; 
        my["con"] = tmpcon; 
        my["dex"] = tmpdex; 
        my["kar"] = 28 + random(3); 
        my["per"] = 28 + random(3); 
        if (dower > 0)
                my["dow"] = dower;
          
/*
        write(HIC "只聽“啪”的一聲，你被濕漉漉的拋了出來。\n" NOR, me); 
        write(sprintf(HIY "\n你這次獲得的四項先天天賦分別是：\n" 
                    "膂力：【 " HIG "%d" HIY " 】 " 
                    "悟性：【 " HIG "%d" HIY " 】 " 
                    "根骨：【 " HIG "%d" HIY " 】 " 
                    "身法：【 " HIG "%d" HIY " 】\n" 
                    "天賦總和為【 " HIR "%d" HIY " 】，如果你滿意，就去投胎(born)吧！方法如" HIR "<born 揚州人氏>\n\n" NOR,
                     tmpstr, tmpint, tmpcon, tmpdex, 80 - dower)); 
*/
        set_temp("washed", 1, me);
  

        set("startroom", "/d/newbie/shijiezhishu", me);
        set("born", "古村", me);
        set("born_family", "沒有", me);
        // 選擇特殊技能
        UPDATE_D->born_player(me);

        me->move("/d/newbie/shijiezhishu");
        set("mud_age", 0, me);
        set("age", 11, me);
        me->save();
        message_vision("$N揉揉眼睛，迷惘的望着這個陌生的世界。\n", me);
        tell_object(me, HIY "新手導師：查看本人所在地的地圖指令map，查看所有地圖指令為map map\n" NOR);
        return 1; 
}

int do_born(string arg)
{
        object me;
        object obj;
        object item;
        mixed dest;
        string new_name;
        string msg;

        if (! objectp(me = this_player()) ||
            ! userp(me))
                return 1;

        if( !query("character", me) )
                return notify_fail("你先選擇(choose)好角色性格，你再投胎也不遲啊！\n");
                
        if( !query_temp("washed", me) )
                return notify_fail("你先在生命池中洗一下(washto)，選擇好天賦你再投胎也不遲啊！\n");

        if (arg && arg[0] < 160)
                return notify_fail("你必須輸入中文地名，比如born 揚州人氏，或者是born 歐陽世家以避免投錯胎。\n");

        new_name = 0;
        if (arg) sscanf(arg, "%s %s", arg, new_name);

        if (! arg || (! stringp(dest = born[arg]) && ! mapp(dest)))
        {
                message_vision("有個聲音惡狠狠的對$N説：你要幹什麼！投胎去哪裏？\n", me);
                return 1;
        }

        if (mapp(dest) && stringp(dest["notice"]))
                return notify_fail(dest["notice"]);

        if (stringp(dest))
        {
                if (! objectp(obj = find_object(dest)))
                        obj = load_object(dest);
                set("startroom", dest, me);
                set("born", arg, me);
                set("born_family", "沒有", me);
        } else
        {
                if (! objectp(obj = find_object(dest["startroom"])))
                        obj = load_object(dest["startroom"]);

                if (new_name)
                {
                        if (! sscanf(new_name, dest["surname"] + "%*s"))
                                new_name = dest["surname"] + new_name;

                        if (strlen(new_name) > 8)
                                return notify_fail("你的名字太長了。\n");

                        if (strlen(new_name) < 4)
                                return notify_fail("你的名字太短了。\n");

                        if (! is_chinese(new_name))
                                return notify_fail("請你用中文起名字。\n");
                }

                if( query("surname", me) != dest["surname"] )
                {
                        // 名字需要變化
                        NAME_D->remove_name(me->name(1),query("id", me));
                        if( !new_name)new_name=dest["surname"]+query("purename", me);
                        if (stringp(msg = NAME_D->invalid_new_name(new_name)))
                        {
                                write(msg);
                                write("你可以考慮在投入世家的時候重新選擇名字：born <世家> <名字>\n");
                                return 1;
                        }
                        set("surname", dest["surname"], me);
                        set("purename", new_name[strlen(dest["surname"])..<1], me);
                        me->set_name();
                        NAME_D->map_name(me->name(1),query("id", me));
                }

                set("startroom", dest["startroom"], me);
                set("born", dest["born"], me);
                set("born_family", arg, me);

                if (mapp(dest["family"]))
                {
                        set("family", dest["family"], me);
                        me->assign_apprentice(dest["family"]["title"], 0);
                }
        }
        if (! objectp(obj))
        {
                message_vision("有個聲音喃喃説道：怎麼好像有問題...\n", me);
                return 1;
        }

        message_vision("一道金光閃過，$N消失得無影無蹤。\n", me);
        
        foreach (item in all_inventory(me))
                if( !query("armor_type", item) )
                {
                        message_vision("$N丟下了$n。\n", me, item);
                        if( item->is_character() || query("value", item) )
                                item->move(environment(me));
                        else
                                destruct(item);
                }

        // 選擇特殊技能
        UPDATE_D->born_player(me);

        me->move(obj);
        set("mud_age", 0, me);
        set("age", 14, me);
        me->save();
        HELP_CMD->main(me, "rules");
        message_vision("$N揉揉眼睛，迷惘的望着這個陌生的世界。\n", me);
        tell_object(me, HIY "新手導師：查看本人所在地的地圖指令map，查看所有地圖指令為map map\n" NOR);

        return 1;
}
