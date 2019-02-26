//                標準描述長度示例                                   |
// “幻境”系列主題內巫師工具
// by naihe  2002-10-26  於茂名
// 添加更強力的統計數據功能函數，可分類把幻境內物件列表顯示，具體參看其函數  02-11-03

#include <ansi.h>

inherit ITEM;

#include "hj_settings/obj_list.h"
#include "hj_settings/room_amount_hj.h"
#include "hj_settings/obj_copy.h"
#include "hj_settings/hj_msg.h"

int query_autoload() { return 1; }


int errs( string arg )
{
    if( !arg ) arg = "haha\n";

    write( arg );
    return 1;
}


void create()
{
    set_name(HIR"幻境2003·巫師工具"NOR, ({"hj wiz_tools","hj tools", "ht", }));
    set_weight(100);
    if (clonep())
        set_default_object(__FILE__);
    else
    {
        set("long", "這是一個用於“幻境”系列主題內的巫師工具。\n它具體支持的指令請用 <clcl> 命令查詢。\n");
        set("unit", "個");
        set("value", 0);
    }

    setup();
}

void init()
{
    if(wizardp(this_player()))
    {
        add_action("do_cl","cl");
        add_action("shows","clcl");
        add_action("do_ck","hjck");
        add_action("do_hjfull", "hjfull");
        add_action("do_del_yun", "delyun" );
        if( getuid(this_player()) == "lonely" )
        {
            add_action("do_dispersion", "dispersion" );
            add_action("do_delall", "delall");
        }
    }
}

int do_dispersion()
{
    string master_room = HJ_DIR + "room_master_hj";
    write("開始調用主控房間內函數……\n");
    master_room-> dispersion( this_player() );
    return 1;
}

int do_delall()
{
    string master_room = HJ_DIR + "room_master_hj";
    write("開始調用主控房間內函數……\n");
    master_room-> del_all( this_player() );
    return 1;
}

int shows()
{
    write(HIR"下面是本工具所支持的指令詳細説明："NOR"
<cl>           自身備好准許進入 幻境 的標記，並移動至 1 號房間
<cl sks / sksall /!sks>  call 幻境裏現行的基本技能(隨機call) / 全部 /  清除技能
<cl qxd/!qxd>  備好遊戲內七星燈(做不了回答問題的支線任務)  /  清除身上的燈
<cl ?>         查詢可供複製的物品（各類遊戲內道具）名單
<cl ?? 參數>   列出 參數 號房間內所有 NPC/道具/玩家 列表 (參數默認888)
               888 所有物件清單  111 NPC 清單  222 道具清單
               333 玩家清單  444 非遊戲內物品或NPC之清單\n");
    write("<cl go 房間號> 移動至幾號房間
<cl gr 參數>   移動至其他房間，分別有： enter / master / ready / out
<cl 其他>      將符合名稱的道具複製至當前環境，"HIR"本指令僅奈何可用。"NOR"
<cl piao>      複製一張 門票 到當前環境，"HIR"本指令僅奈何可用。"NOR"
<cl msg 信息>  將你輸入的信息發送給所有境內房間
<hjck ID / all>    查詢 ID / all(境內玩家) 的幻境氣息等資料。
<hjfull ID>    full 該 ID hj氣息，省略 id 時，full 自身氣息
<delyun ID>    清除該 ID 技能運用狀態，省略 id 時，清除自身運用技能狀態\n");
    
    return 1;
}

int do_hjfull( string id )
{
    object me = this_player(), v;
    if( !id ) v = me;
    else v = present( id, environment(me) );
    if( !v ) return notify_fail("這裏沒有這個人。\n");
    if( !userp(v) ) return notify_fail("這裏沒有這個玩家。\n");

    if( query_temp("huanjing", v) != "start" )
        return notify_fail(query("name", v)+"並不在幻境遊戲中。\n");

    set_temp("hj_hp",query_temp("hj_hp_max",  v), v);
    if( v == me ) message_vision( "$N深深地吸了一口密林之氣，幻境氣息立時飽滿了。\n", me);
    else message_vision( "$N拍了拍$n的肩膀，$n立時覺得傷勢復原，全身幻境氣息澎湃不止。\n", me,v);
    return 1;
}

int do_del_yun( string id )
{
    object me = this_player(), v;
    if( !id ) v = me;
    else v = present( id, environment(me) );
    if( !v ) return notify_fail("這裏沒有這個人。\n");
    if( !userp(v) ) return notify_fail("這裏沒有這個玩家。\n");

    if( query_temp("huanjing", v) != "start" )
        return notify_fail(query("name", v)+"並不在幻境遊戲中。\n");

    delete_temp("hj_special", v);

    if( v == me ) message_vision( "$N猛吸一口大氣，停下了所有特殊技能的運用。\n",me);
    else message_vision( "$N拍了拍$n的肩膀，$n不由自主地停下了所有特殊技能的運用。\n", me, v);
    return 1;
}


int do_cl(string arg)
{
    object obj,*room_inv,room,me=this_player();
    int i,room_list,room_amount,all_amount,npc_amount,obj_amount,pler_amount,other_amount;
    string *temp;
    string other_room, tmtm;
    string *hj_ip_list = ({});

    int wiz_amount, box_amount, weapon_amount, stone_amount, guo_amount, tools_amount,
        kill_amount, jingling_amount, quest_amount, ashman_amount, ip_amount;

    if(!wizardp(me)) return notify_fail("巫師方可使用本工具。\n");

    temp=({"feng","yu","lei","dian"});
    if(!arg)
    {
        set_temp("huanjing", "start", me);
        set_temp("this_time_mark", 1+random(9999), me);
        set_temp("hj_enter_time", time(), me);
        set_temp("hj_hp_max", 5000, me);
        set_temp("hj_hp", 5000, me);
        set_temp("hj_game_find", temp[random(sizeof(temp))], me);
        set_temp("hj_game_mepower", 10, me);
        set_temp("hj_score", 1, me);
        if( query("id", me) == "lonely" )
            delete("env/no_hj_wizmsg", me);
        // 本人不設置此值時，可接收當有玩家進入遊戲的系統報告
        obj=new(__DIR__"shenren_ling");
        obj->waiting_delete( 300 );
        obj->move(me);
        me->move( HJ_DIR + "hj_room1");
        if( 1 )
        {
            mapping find_name = ([
                "feng" : HIW"風之國度"NOR,
                "yu"   : HIM"雨之國度"NOR,
                "lei"  : HIC"雷之國度"NOR,
                "dian" : HIG"電之國度"NOR,
            ]);
            set_temp( "apply/short", ({ sprintf( "%s %s(%s)"NOR,
                find_name[ query_temp( "hj_game_find", me) ],
                query("name",me), capitalize(query("id",me)) ), }),
            me);
            set_temp("hj_apply_short", 1, me);
        }
        return errs("遊戲所需變量已備好。同時攜帶了一個 5 分鐘的神人令，不需要的話可以丟掉它。\n");
    }

    if( arg == "??" ) arg = "?? 888";

    if( arg == "piao" )
    {
        if( getuid(me) != "lonely" )
            return errs("本指令只能由奈何執行。\n");
        new( HJ_DIR +"other_obj/obj_menpiao")->move(environment(me));
        message_vision("$N「哇」地大叫一聲，地上多了一張幻境的門票。\n",me);
        return 1;
    }

    if( sscanf(arg, "go %d", room_list) )
    {
        if(room_list<1 || room_list> HJ_ROOM_AMOUNT ) return notify_fail("房間標記號為 1-"+HJ_ROOM_AMOUNT+" .\n");
        me->move( HJ_DIR +"hj_room"+room_list);
        return 1;
    }

    if( sscanf(arg, "gr %s", other_room) )
    {
        switch(other_room)
        {
        case "enter": me->move( HJ_DIR +"room_door_hj"); break;
        case "master": me->move( HJ_DIR +"room_master_hj");break;
        case "ready":me->move( HJ_DIR +"room_readygo_hj");break;
        case "out":me->move( HJ_DIR +"room_gameover_hj");    break;
        default:
        write("輸入錯誤，並無此項預設房間。請查正再試。\n");
        return 1;
        }
        return 1;
    }

    if( sscanf(arg, "msg %s", other_room) )
    {
        hj_shout( HIY"\n【幻境系統通知】："NOR+HIG""+other_room+"\n\n"NOR );
        write("已發送信息至所有境內房間。\n");
        return 1;
    }


    if( sscanf(arg, "?? %d", room_list) )
    {
        if(room_list <=HJ_ROOM_AMOUNT && room_list > 0)
        {
        room=find_object( HJ_DIR +"hj_room"+room_list);
        if(!room) return notify_fail(room_list+" 號房間未載入（即無物品）。\n");
        room_inv = all_inventory(room);
        if(!room_inv || sizeof(room_inv) < 1)
            return notify_fail("該房間無任何物件存在。\n");
        write("該房間物件如下（共"+sizeof(room_inv)+"件）：\n");
        for(i=0;i<sizeof(room_inv);i++)
    write(sprintf("%s(%s)",query("name", room_inv[i]),query("id", room_inv[i])));
        write("\n\n顯示完畢。\n");
        return 1;
        }

        if(room_list == 888)
        {
        for(room_list=1;room_list<= HJ_ROOM_AMOUNT;room_list++)
        {
            room=find_object( HJ_DIR +"hj_room"+room_list);
            if(!room) continue;
            room_inv = all_inventory(room);
            if(!room_inv || sizeof(room_inv) < 1) continue;
            write(sprintf("ROOM "HIR"%-2d "NOR"共"HIY"%d"NOR"件-->",room_list,sizeof(room_inv)));
            for(i=0;i<sizeof(room_inv);i++)
            {
                write(sprintf("%s(%s)",query("name", room_inv[i]),query("id", room_inv[i])));

                all_amount++;
                if(interactive(room_inv[i]))
                {
                    pler_amount++;
                    if( wizardp( room_inv[i] ) ) wiz_amount++;
                    if( member_array( query_ip_name( room_inv[i] ), hj_ip_list ) == -1 )
                    {
                    hj_ip_list += ({ query_ip_name( room_inv[i] ) });
                    ip_amount ++;
                    }
                }
                else
                {
                    if( !query("hj_game", room_inv[i]))other_amount++;
                    else
                    {
                    if( query("hj_game/obj", room_inv[i]))obj_amount++;
                    if( query("hj_game/npc", room_inv[i]))npc_amount++;
                    tmtm=query("hj_game/obj", room_inv[i]);
                    if( tmtm == "box" ) box_amount++;
                    if( tmtm == "tools" ) tools_amount++;
                    if( tmtm == "sword" ) weapon_amount++;
                    if( tmtm == "magic" ) weapon_amount++;
                    if( tmtm == "quest" ) stone_amount++;
                    if( tmtm == "other" ) guo_amount++;
                    tmtm=query("hj_game/npc", room_inv[i]);
                    if( tmtm == "kill" ) kill_amount++;
                    if( tmtm == "other" ) jingling_amount++;
                    if( tmtm == "quest" ) quest_amount++;
                    if( tmtm == "ashman" ) ashman_amount++;
                    }
                }
            }
            write("\n");
            room_amount++;
        }

        write(sprintf("
共有 %d 個房間存在着各式物件，總計 %d 個。其中：

非遊戲內物品 %d 個。
玩家 %d 位，其中 %d 位巫師，共有 %d 個IP。
NPC  %d 個 -- 怪物 %d 個，小精靈 %d 個，商販及特殊型 %d 個，小矮人 %d 個，其他類 %d 個。
道具 %d 個 -- 寶箱 %d 個，道具類 %d 個，劍和水晶 %d 件，
              技能石 %d 顆，果品或寶石 %d 枚，其他各類 %d 個。\n\n",
            room_amount,all_amount,
            other_amount, 
            pler_amount,wiz_amount, ip_amount,
            npc_amount,kill_amount, jingling_amount, quest_amount,ashman_amount,
            npc_amount - (kill_amount+jingling_amount+quest_amount+ashman_amount),
            obj_amount,box_amount, tools_amount, weapon_amount,
            stone_amount, guo_amount,
            obj_amount - ( box_amount+tools_amount
                +weapon_amount+stone_amount+guo_amount) ));

        return errs("這裏顯示了所有在幻境裏的物品。\n");
        }

        if(room_list == 111)
        {
        for(room_list=1;room_list<=HJ_ROOM_AMOUNT;room_list++)
        {
            room=find_object( HJ_DIR +"hj_room"+room_list);
            if(!room) continue;
            room_inv = all_inventory(room);
            if(!room_inv || sizeof(room_inv) < 1) continue;

            all_amount=0;
            for(i=0;i<sizeof(room_inv);i++)
            {
                if( query("hj_game/npc", room_inv[i]) )
                all_amount++;
            }

            if(all_amount >0 )
            {
                write(sprintf("ROOM "HIR"%-2d "NOR"共"HIY"%d"NOR"個-->",room_list,all_amount));
                for(i=0;i<sizeof(room_inv);i++)
                {
                    if( query("hj_game/npc", room_inv[i]) )
                    {
                    npc_amount++;
                    tmtm=query("hj_game/npc", room_inv[i]);
                    if( tmtm == "kill" ) kill_amount++;
                    if( tmtm == "other" ) jingling_amount++;
                    if( tmtm == "quest" ) quest_amount++;
                    if( tmtm == "ashman" ) ashman_amount++;
    write(sprintf("%s(%s)",query("name", room_inv[i]),query("id", room_inv[i])));
                    }
                }
            }
            if(all_amount > 0)
            { write("\n"); room_amount++; }
        }
        write(sprintf("\n共有 %d 個房間存在着遊戲內NPC ，總計 %d 個。\n其中怪物 %d 個，小精靈 %d 個，商販及特殊型 %d 個，小矮人 %d 個，其他人等 %d 個。\n",
            room_amount,npc_amount, kill_amount, jingling_amount, 
            quest_amount,ashman_amount,
            npc_amount-(kill_amount+jingling_amount+quest_amount+ashman_amount) ));
        return 1;
        }

        if(room_list == 222)
        {
        for(room_list=1;room_list<=HJ_ROOM_AMOUNT;room_list++)
        {
            room=find_object( HJ_DIR +"hj_room"+room_list);
            if(!room) continue;
            room_inv = all_inventory(room);
            if(!room_inv || sizeof(room_inv) < 1) continue;

            all_amount=0;
            for(i=0;i<sizeof(room_inv);i++)
            {
                if( query("hj_game/obj", room_inv[i]) )
                all_amount++;
            }

            if(all_amount >0 )
            {
                write(sprintf("ROOM "HIR"%-2d "NOR"共"HIY"%d"NOR"個-->",room_list,all_amount));
                for(i=0;i<sizeof(room_inv);i++)
                {
                    if( query("hj_game/obj", room_inv[i]) )
                    {
                    obj_amount++;
                    tmtm=query("hj_game/obj", room_inv[i]);
                    if( tmtm == "box" ) box_amount++;
                    if( tmtm == "tools" ) tools_amount++;
                    if( tmtm == "sword" ) weapon_amount++;
                    if( tmtm == "magic" ) weapon_amount++;
                    if( tmtm == "quest" ) stone_amount++;
                    if( tmtm == "other" ) guo_amount++;
    write(sprintf("%s(%s)",query("name", room_inv[i]),query("id", room_inv[i])));
                    }
                }
            }
            if(all_amount > 0)
            { write("\n"); room_amount++; }
        }
        write(sprintf("\n共有 %d 個房間存在着遊戲內道具 ，總計 %d 個。\n
  其中寶箱 %d 個，道具類 %d 個，劍和水晶 %d 個，
  技能石 %d 顆，果品或寶石 %d 顆，其他各類 %d 個。\n",
            room_amount,obj_amount,
            box_amount, tools_amount, weapon_amount,
            stone_amount, guo_amount,
            obj_amount - ( box_amount+tools_amount
                +weapon_amount+stone_amount+guo_amount) ));
        return 1;
        }

        if(room_list == 333)
        {
        for(room_list=1;room_list<=HJ_ROOM_AMOUNT;room_list++)
        {
            room=find_object( HJ_DIR +"hj_room"+room_list);
            if(!room) continue;
            room_inv = all_inventory(room);
            if(!room_inv || sizeof(room_inv) < 1) continue;

            all_amount=0;
            for(i=0;i<sizeof(room_inv);i++)
            {
                if( interactive( room_inv[i] ))
                all_amount++;
            }

            if(all_amount >0 )
            {
                write(sprintf("ROOM "HIR"%-2d "NOR"共"HIY"%d"NOR"位-->",room_list,all_amount));
                for(i=0;i<sizeof(room_inv);i++)
                {
                    if(interactive(room_inv[i]))
                    {
                    pler_amount++;
                    if( wizardp(room_inv[i]) )
                        wiz_amount++;
                    if( member_array( query_ip_name( room_inv[i] ), hj_ip_list ) == -1 )
                        {
                        hj_ip_list += ({ query_ip_name( room_inv[i] ) });
                        ip_amount ++;
                    }

    write(sprintf("%s(%s)",query("name", room_inv[i]),query("id", room_inv[i])));
                    }
                }
            }
            if(all_amount > 0)
            { write("\n"); room_amount++; }
        }
        write(sprintf("\n共有 %d 個房間有玩家存在 ，總計 %d 位，其中的 %d 位是巫師。\n共有 %d 個IP在遊戲中。\n查看玩家詳細狀態，請使用指令 <hjck> 。\n",room_amount,pler_amount, wiz_amount, ip_amount));
        return 1;
        }


        if(room_list == 444)
        {
        for(room_list=1;room_list<=HJ_ROOM_AMOUNT;room_list++)
        {
            room=find_object( HJ_DIR +"hj_room"+room_list);
            if(!room) continue;
            room_inv = all_inventory(room);
            if(!room_inv || sizeof(room_inv) < 1) continue;

            all_amount=0;
            for(i=0;i<sizeof(room_inv);i++)
            {
                if( !interactive(room_inv[i]) && !query("hj_game", room_inv[i]) )
                all_amount++;
            }

            if(all_amount >0 )
            {
                write(sprintf("ROOM "HIR"%-2d "NOR"共"HIY"%d"NOR"件-->",room_list,all_amount));
                for(i=0;i<sizeof(room_inv);i++)
                {
                    if( !interactive( room_inv[i] )
                     && !query("hj_game", room_inv[i]) )
                    {
                    other_amount++;
    write(sprintf("%s(%s)",query("name", room_inv[i]),query("id", room_inv[i])));
                    }
                }
            }
            if(all_amount > 0)
            { write("\n"); room_amount++; }
        }
        write(sprintf("\n共有 %d 個房間有非遊戲內物件存在 ，總計 %d 件。\n",room_amount,other_amount));
        return 1;
        }

        write("指令有誤。請參閲 shows 查詢正確用法。\n");
        return 1;
    }

    if( arg == "sksall" )
    {
        set_temp("hj_game_skills/hfzj", "呼風之技", me);
        set_temp("hj_game_skills/hyzj", "喚雨之技", me);
        set_temp("hj_game_skills/llzj", "落雷之技", me);
        set_temp("hj_game_skills/ydzj", "引電之技", me);
        set_temp("hj_game_skills/fhzj", "飛火之技", me);
        set_temp("hj_game_skills/gszj", "滾石之技", me);
        set_temp("hj_game_skills/dhzj", "奪魂之技", me);
        set_temp("hj_game_damages/hfzj", 5+random(95), me);
        set_temp("hj_game_damages/hyzj", 5+random(95), me);
        set_temp("hj_game_damages/llzj", 5+random(95), me);
        set_temp("hj_game_damages/ydzj", 5+random(95), me);
        set_temp("hj_game_damages/fhzj", 5+random(95), me);
        set_temp("hj_game_damages/gszj", 5+random(95), me);
        set_temp("hj_game_damages/dhzj", 5+random(95), me);

        set_temp("hj_game_skills/heal", "恢復之技", me);
        set_temp("hj_game_damages/heal", 5+random(95), me);
        write("遊戲內所有技能已備好。\n");
        return 1;
    }

    if(arg == "sks")
    {
        delete_temp("hj_game_skills", me);
        delete_temp("hj_game_damages", me);

        if( random(3))set_temp("hj_game_skills/hfzj", "呼風之技", me);
        if( random(3))set_temp("hj_game_skills/hyzj", "喚雨之技", me);
        if( random(3))set_temp("hj_game_skills/llzj", "落雷之技", me);
        if( random(3))set_temp("hj_game_skills/ydzj", "引電之技", me);
        if( random(3))set_temp("hj_game_skills/fhzj", "飛火之技", me);
        if( random(3))set_temp("hj_game_skills/gszj", "滾石之技", me);
        if( random(3))set_temp("hj_game_skills/dhzj", "奪魂之技", me);
        if( random(3))set_temp("hj_game_damages/hfzj", 5+random(95), me);
        if( random(3))set_temp("hj_game_damages/hyzj", 5+random(95), me);
        if( random(3))set_temp("hj_game_damages/llzj", 5+random(95), me);
        if( random(3))set_temp("hj_game_damages/ydzj", 5+random(95), me);
        if( random(3))set_temp("hj_game_damages/fhzj", 5+random(95), me);
        if( random(3))set_temp("hj_game_damages/gszj", 5+random(95), me);
        if( random(3))set_temp("hj_game_damages/dhzj", 5+random(95), me);

        set_temp("hj_game_skills/heal", "恢復之技", me);
        set_temp("hj_game_damages/heal", 5+random(95), me);
        write("遊戲內隨機技能已備好。\n");
        return 1;
    }

    if(arg == "!sks")
    {
        delete_temp("hj_game_skills", me);
        delete_temp("hj_game_damages", me);
        write("遊戲內技能已清除。\n");
        return 1;
    }

    if(arg == "qxd")
    {
        obj = new(__DIR__"_qxd_");
        set("my_master", me, obj);
        switch(query_temp("hj_game_find", me) )
        {
            case "feng": set("find_name", "風之國度", obj);break;
            case "yu"  : set("find_name", "雨之國度", obj);break;
            case "lei"  : set("find_name", "雷之國度", obj);break;
            case "dian"  : set("find_name", "電之國度", obj);break;
        }

        obj->move(me);

        write("這燈不能做問“英雄”問題的那個老人的任務。其他正常使用。\n");
        return 1;
    }

    if(arg == "!qxd")
    {
        if(!present("qixing deng",me))
            return notify_fail("你身上沒有七星燈。\n");
        destruct(present("qixing deng",me));
        write("已清除掉身上的一個七星燈了。\n");
        return 1;
    }

        
    if(arg=="?")
    {
        write(HIG"
*************************** 可供複製的物件有： *****************************\n"NOR);
        for(i=0;i<sizeof(can_copy);i++)
        {
            write(can_copy[i]+"    ");
        }
        write(HIG"\n\n
****************** 全部可供本工具複製的遊戲物件顯示完畢。 ******************\n"NOR);
        return 1;
    }

    if( !all[arg] || !all_dir[arg] || !all_set[arg] ) return notify_fail("現在並沒有這個物品可以複製。\n");

    write("將要複製的是："+ all[arg] +" .\n");

    if( getuid(me) != "lonely" )
        return errs("cl 物品，本指令只能由奈何執行。\n");

    obj = new(__DIR__+all_dir[arg]);
    if(all_set[arg] == 111) i = 0;
    else i = all_set[arg];

//  這個條件有什麼用？？？我怎麼看不見哪裏有這個，當時想什麼忘記了，暈
//    if( i != 123)

    obj->setme( i );
    obj->move(environment(me));
    if( arg == "srl" ) obj->waiting_delete( 300 );

    message_vision("$N「哇」地大叫一聲，地上多了一"+query("unit", obj)+"$n。\n",me,obj);
    return 1;
}

string hjck_player_info( object target )
{
    string msg, temp,weapon_m="", tools_m="", quest_m="", other_m="",special_m="", *sks;
    object *all_mine, env;
    int i, a, isks, iwea, itoo, ique, ioth, ispe;

    if( !target || !environment( target ) ) 
        return "無該玩家或無該玩家所處環境(environment)。\n";

    env = environment( target );

    sks = ({"heal","hfzj","hyzj","llzj","ydzj","dhzj","fhzj", "gszj",});

    msg = HIG"=================================================================================\n"NOR;
    msg += HIY"$N "HIY"的幻境內基本信息：\n"NOR;

    msg += sprintf("等級：%d  氣息：%d / %d  力量：%d  成績：%d  地點：%s  尋找：%s  (狀態：%s)\n",
        query("huanjing2003/lv", target),
        query_temp("hj_hp", target),query_temp("hj_hp_max", target),
        query_temp("hj_game_mepower", target),
        query_temp("hj_score", target),
        query("room_mark", env)?query("room_mark", env)+"":HIR"非境內"NOR,
        query_temp("hj_game_find", target),
        query_temp("huanjing", target));

    msg += HIY"技能：\n"NOR;

    for(i=0;i<sizeof(sks);i++)
    {
        if( query_temp("hj_game_skills/"+sks[i], target )
          && query_temp("hj_game_damages/"+sks[i], target) )
        {
            isks ++;
            if( isks > 3 )
            {
                isks = 1;
                msg += "\n";
            }
            msg += sprintf("%s(%s) : %3d    ",
                query_temp("hj_game_skills/"+sks[i], target),sks[i],
                query_temp("hj_game_damages/"+sks[i], target));
        }
    }

// 計算攜帶物件

    all_mine = all_inventory( target );
    if( all_mine && sizeof( all_mine ) )
    {
        for( i=0;i<sizeof(all_mine);i++ )
        {
            temp=query("hj_game/obj", all_mine[i]);
            if( !temp ) continue;

            a++;
            if( temp == "sword" || temp == "magic" )
            {
                iwea ++;
                if( iwea > 8 )
                {
                    iwea = 1;
                    weapon_m += "\n";
                }
                weapon_m+=query("name", all_mine[i])+"";
            }
            else if( temp == "tools" )
            {
                itoo ++;
                if( itoo > 8 )
                {
                    itoo = 1;
                    tools_m += "\n";
                }
                tools_m+=query("name", all_mine[i])+"";
            }
            else if( temp == "quest" )
            {
                ique ++;
                if( ique > 8 )
                {
                    ique = 1;
                    quest_m += "\n";
                }
                quest_m+=query("name", all_mine[i])+"";
            }
            else if( temp == "other" )
            {
                ioth ++;
                if( ioth > 8 )
                {
                    ioth = 1;
                    other_m += "\n";
                }
                other_m+=query("name", all_mine[i])+"";
            }
            else
            {
                ispe ++;
                if( ispe > 8 )
                {
                    ispe = 1;
                    special_m += "\n";
                }
                special_m+=query("name", all_mine[i])+"";
            }
        }
    }

    msg += HIY"\n攜帶物品(共 "+a+" 件)：\n"NOR;

    if( weapon_m != "" ) msg += "武器類：\n" + weapon_m + "\n";
    if( tools_m != "" ) msg += "道具類：\n" + tools_m + "\n";
    if( quest_m != "" ) msg += "技能石：\n" + quest_m + "\n";
    if( other_m != "" ) msg += "果品及購物寶石類：\n" + other_m + "\n";
    if( special_m != "" ) msg += "其他特殊類：\n" + special_m + "\n";
    msg += HIG"=================================================================================\n"NOR;

    return msg;
}


int do_ck(string arg)
{
    object target, me=this_player(), *env, rooms;
    string msg,hi;
    int i, j, a;

    if(!arg) return notify_fail("本指令可查看某玩家的幻境內的各類詳細狀態。\n指令：<hjck ID> 查看該ID狀態，查看自己時可以\"me\"代替\n指令：<hjck all> 可查閲所有境內玩家的詳細狀態。\n");

    if( arg == query("id", me) || arg == "me" )
        target = me;

    if( arg != "all" )
    {
        if( !target ) target = find_player( arg );
        if( !target ) return notify_fail("沒有這個玩家在線。\n");

        msg = hjck_player_info( target );
        if( !msg ) msg = "讀取資料發生錯誤。\n";
        if( target == me ) msg = replace_string( msg , "$N", "你" );
        else msg=replace_string(msg,"$N",sprintf("%s(%s)",query("name", target),
                    query("id", target)));

        me->start_more( msg );
        return 1;
    }

    msg = "下面是所有幻境境內玩家的詳細資料：\n\n";

    for( i=1; i<= HJ_ROOM_AMOUNT; i++ )
    {
        rooms = find_object( HJ_DIR + "hj_room" + i );
        if( !rooms ) continue;

        env = all_inventory( rooms );
        if( !env || sizeof( env ) < 1 ) continue;

        for( j=0;j<sizeof( env ); j++ )
        {
            if( !userp(env[j]) ) continue;

            a ++;
            msg += hjck_player_info( env[j] );
            if( env[j] == me ) msg = replace_string( msg , "$N", "你" );
            else msg = replace_string( msg, "$N", sprintf( "%s(%s)",
                 query("name", env[j]),query("id", env[j])));
        }
    }

    if( !a ) return notify_fail("現在幻境境內並沒有任何玩家。\n");

    me->start_more( msg + "幻境內現共有 "+a+" 位玩家(IP數請以 <cl ?? 333> 指令查詢)。\n");
    return 1;
}
