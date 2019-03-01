// team.c
// Written by Lonely@nitan.org (16/05/2009)

#include <ansi.h>
#include <command.h>
#include <origin.h>

/*
object can_guard()              // 是否有人替此人當招
void release_array()            // 解散陣法
int refresh_array()             // 刷新陣員: 1 陣法正常 0 陣法被解散
*/
class zhenfa
{
        object *memb;           // 陣法成員
        string type;            // 陣法的武功類型
        int num;                // 陣法的要求人數
        object master;          // 陣主
        string name;            // 陣法名稱
        string menpai;          // 陣法所屬門派
        int ready;              // 組陣完成
        int array_level;        // 陣法的整體有效值
        int level;              // 此陣法的有效等級
        string zhen_fn;         // 陣法文件名
}

/* 成陣因素
1。成員為同一門派
2。都會並且 enable 同一陣法
3。當前所使用兵器為陣法要求的兵器
4。達到陣法要求人數
5。環境相同

移動成員均跟隨陣主
心跳刷新陣法狀態
兵器的狀態變化要查詢陣法 enable zhuang xie
陣法在戰鬥中的威力：
        替弱者抵擋：當人 busy，氣過于少、神過于低。替人抵擋一招自己停一照
        陣法成員進入戰鬥狀態，陣員會全員加入、陣法開始起作用
        陣法的特攻 謎幻敵人是敵人的招數落空

*/

class team
{
        object *memb;
        object leader;
}

nosave class zhenfa zhen;
nosave object leader;
nosave class team oteam;

//protected 
void init_zhen()
{
        zhen = new(class zhenfa);
        zhen->memb = ({});
}

// 以下為查詢函數
int in_array()
{
        if(!classp(zhen))
                return 0;

        if(!arrayp(zhen->memb))
                return 0;

        zhen->memb -= ({0});
        return sizeof(zhen->memb);
}

object query_array_obstructor()
{
        if(!in_array() || !zhen->ready)
                return 0;

        foreach(object ob in zhen->memb)
        {
                mapping db;

                if(!ob
                || (ob == this_object())
                || ob->is_busy())
                        continue;

                db = ob->query_entire_dbase();
                if( (db["kee"] > db["max_kee"]*3/5)
                && (db["sen"] > db["max_sen"]*3/5) )
                        return ob;
        }

        return 0;
}

int query_array_level()
{
        if(!in_array() || !zhen->ready)
                return 0;

        return zhen->array_level>4000?4000:zhen->array_level;
}

void check_array_status()
{
        int i,n;
        string ski;

        if(!in_array())
                return;

        if((n=sizeof(zhen->memb)) < zhen->num)
        {
                if(zhen->ready)
                        zhen->ready = 0;
                return;
        }

        ski = zhen->zhen_fn->query_array_id();
        zhen->array_level = 0;

        for(i=0;i<n;i++)
        {
                if(!living(zhen->memb[i]))
                        break;

                if(zhen->memb[i]->query_temp("on_rided"))
                        break;

                if(zhen->memb[i]->query_current_skill() != zhen->type)
                        break;

                if(environment(zhen->memb[i]) != environment(zhen->master))
                        break;

                zhen->array_level += zhen->memb[i]->query_skill(ski,1);

                if(zhen->memb[i] == zhen->master)
                        continue;
        }

        if(i<n)
        {
                if(zhen->ready)
                        zhen->ready = 0;
                return;
        }

        zhen->array_level = (zhen->array_level)*(zhen->level)/(zhen->num);

        if(!zhen->ready)
        {
                zhen->ready = 1;
                message_vision((zhen->zhen_fn)->success_msg(),zhen->master);
        }
}

string query_array_name()
{
        if(!classp(zhen))
                return 0;

        return zhen->name;
}

object query_array_master()
{
        if(!classp(zhen))
                return 0;

        return zhen->master;
}

object *query_array_member()
{
        if(!classp(zhen))
                return 0;

        return zhen->memb;
}

string query_array_fn() { return zhen->zhen_fn; }

int query_array_status() { return classp(zhen) && zhen->ready && (sizeof(zhen->memb - ({0})) >= zhen->num); }

// 以下為判斷函數
int can_become_member(object who)
{
        if(!who)
                return 0;

        if(environment(who) != environment())
                return notify_fail("沒有這個人。\n");

        if(!in_array())
                return notify_fail("你沒有在任何陣形之中。\n");

        if(zhen->master != this_object())
                return notify_fail("你並不是陣主。\n");

        if(sizeof(zhen->memb) >= zhen->num)
                return notify_fail(sprintf("『%s』的人數已經夠%s個人了。\n",
                        zhen->name,
                        chinese_number(zhen->num)));

        if(!living(who))
                return notify_fail(who->name()+"目前無法聽見你說話，等會兒再說吧。\n");

        if(!zhen->zhen_fn)
        {
                init_zhen();
                return 0;
        }

        if(!zhen->zhen_fn->valid_member(who))
                return 0;

        return 1;
}

int is_array_member(object who)
{
        if(!who || !in_array())
                return 0;
        return member_array(who,zhen->memb) != -1;
}

int is_array_master()
{
        return in_array() && (zhen->master == this_object());
}

// 以下為狀態變更函數
int set_array(class zhenfa z)
{
        if(!classp(z))
                return 0;

        if( !z->master
        || !previous_object()
        || (previous_object() != z->master) )
                return 0;

        zhen = z;
        return 1;
}

int add_array_member(object who)
{
        if(!can_become_member(who))
                return 0;

        foreach(object ob in zhen->memb)
                if(who->is_fighting(ob))
                        return notify_fail(sprintf("你正在和『%s』的成員%s打架呢！\n",
                                zhen->name,ob->name()));

        zhen->memb += ({ who });

        if(!who->set_array(zhen))
        {
                zhen->memb -= ({ who });
                return notify_fail("加入陣法成員失敗。\n");
        }

        tell_object(this_object(),sprintf("%s應邀加入你主持的『%s』。\n",
                who->name(),zhen->name));
        message("tell_object",sprintf("【%s】：%s應邀加入『%s』。\n",
                zhen->name,who->name(),zhen->name),(zhen->memb - ({who})) );

        check_array_status();

        return 1;
}

int build_up_array(string f_name)
{
        if(in_array())
        {
                tell_object(this_object(),sprintf("你正在『%s』中，無法再主持其它陣法。\n",
                        zhen->name));
                return 0;
        }

        if(!f_name || (file_size(f_name+".c") <= 0))
        {
                tell_object(this_object(),"陣法錯誤！\n");
                return 0;
        }

        init_zhen();

        zhen->memb += ({ this_object() });
        zhen->master = this_object();
        zhen->num = f_name->query_member_num();
        zhen->name = f_name->query_name();
        zhen->menpai = f_name->query_menpai();
        zhen->zhen_fn = f_name;
        zhen->type = f_name->query_array_skill();
        zhen->level = f_name->query_effective_level();

        if(!zhen->num || !zhen->name || !zhen->type || !zhen->level)
        {
                init_zhen();
                tell_object(this_object(),"陣法參數錯誤。\n");
                return 0;
        }

        return 1;
}

varargs int release_array(int flag)
{
        object me = this_object();

        if(!in_array())
                return notify_fail("你並沒有在任何陣法之中。\n");

        if(zhen->master != me)
                return notify_fail(sprintf("只有陣主才能解散『%s』。\n",zhen->name));

        zhen->memb -= ({ me });

        switch (flag)
        {
                case 0: // array 命令主動解散
                        if(sizeof(zhen->memb))
                                message("tell_object",sprintf("【%s】：%s將『%s』解散了。\n",
                                        zhen->name,me->name(),zhen->name),zhen->memb );
                        tell_object(me,sprintf("你將『%s』解散了。\n",zhen->name));
                        break;

                case 1: // 陣主死亡
                        if(sizeof(zhen->memb))
                                message("tell_object",sprintf("【%s】：由于陣主%s死亡，『%s』解散了。\n",
                                        zhen->name,me->name(),zhen->name),zhen->memb );
                        break;

                case 2: // 陣主離開遊戲
                        if(sizeof(zhen->memb))
                                message("tell_object",sprintf("【%s】：由于陣主%s離開遊戲，『%s』解散了。\n",
                                        zhen->name,me->name(),zhen->name),zhen->memb );
                        break;

                case 3: // 失散
                        //if(sizeof(zhen->memb))
                        //      message("tell_object",sprintf("【%s】：由于和陣主%s失散，『%s』解散了。\n",
                        //              zhen->name,me->name(),zhen->name),zhen->memb );
                        tell_object(me,sprintf("由于沒有其他成員，『%s』自動解散了。\n",zhen->name));
                        break;
                case 4: // 昏迷不醒
                        if(sizeof(zhen->memb))
                                message("tell_object",sprintf("【%s】：由于陣主%s昏迷不醒，『%s』解散了。\n",
                                        zhen->name,me->name(),zhen->name),zhen->memb );
                        break;
                case 5:
                        if(sizeof(zhen->memb))
                                message("tell_object",sprintf("【%s】：由于內部成員發生內訌，『%s』解散了。\n",
                                        zhen->name,zhen->name),zhen->memb );
                        break;
        }

        if(sizeof(zhen->memb))
                (zhen->memb)->init_zhen();

        init_zhen();
        return 1;
}

// 以下為狀態改變通知
varargs void dismiss_array_member(object who,int flag) // 隊員離隊
{
// flag = 4 昏迷不醒
// flag = 3 走失
// flag = 2 quit
// flag = 1 dead
        string out;

        if(!objectp(who)
        || !in_array()
        || (who == zhen->master)
        || (zhen->master != this_object())
        || (member_array(who,zhen->memb) == -1) )
                return;

        zhen->memb -= ({ who });
        who->init_zhen();
        tell_object(who,sprintf("\n你脫離了『%s』。\n\n",zhen->name));

        if(sizeof(zhen->memb) <= 1)// 由于和其他成員失散
        {
                tell_object(zhen->master,sprintf("\n%s脫離了『%s』。\n\n",who->name(),zhen->name));
                release_array(3);
                return;
        }

        switch (flag)
        {
                case 4:
                        out = "昏迷不醒";
                        break;
                case 2:
                        out = "離開遊戲";
                        break;
                case 1:
                        out = "死亡";
                        break;
                default:
                        out = "脫離了陣法";
                        break;
        }

        if(zhen->ready)
        {
                message("tell_object",sprintf("【%s】：由于%s%s，『%s』的威力消失了。\n",
                        zhen->name,who->name(),out,zhen->name),zhen->memb );
                zhen->ready = 0;
        }
        else
                message("tell_object",sprintf("【%s】：由于%s%s，『%s』失去了一名成員。\n",
                        zhen->name,who->name(),out,zhen->name),zhen->memb );

}

void test_array()
{
        object me = this_object(),*lv = ({}),env = environment();
        int i,n;

        if( !(n = in_array()) || (n == 1))
                return;

        if(zhen->master == me)
        {
                for( i=0;i<n;i++ )
                        if(environment(zhen->memb[i]) != env)
                                lv +=({  zhen->memb[i] });
                if(n = sizeof(lv))
                {
                        string out = "";

                        zhen->memb -= lv;

                        message("tell_object",sprintf("你脫離了『%s』。\n",zhen->name),lv);
                        lv->init_zhen();

                        switch (n)
                        {
                                case 1:
                                        out = lv[0]->name();
                                        break;
                                case 2:
                                        out = sprintf("%s和%s",lv[0]->name(),lv[1]->name());
                                        break;
                                default:
                                        for(i=0;i<n;i++)
                                                out += i==0?lv[i]->name():
                                                        ( (i==n-1)?sprintf("和%s",lv[i]->name()):
                                                                sprintf("、%s",lv[i]->name()) );
                        }

                        if(sizeof(zhen->memb) <= 1)
                        {
                                tell_object(me,sprintf("【%s】：%s脫離了陣法。\n",
                                        zhen->name,out));
                                release_array(3);
                                return;
                        }

                        else if(zhen->ready)
                        {
                                message("tell_object",sprintf("【%s】：由于%s脫離了陣法，『%s』的威力消失了。\n",
                                        zhen->name,out,zhen->name),zhen->memb);
                                zhen->ready = 0;
                        }
                        else
                                message("tell_object",sprintf("【%s】：%s脫離了『%s』。\n",
                                        zhen->name,out,zhen->name),zhen->memb);
                }
                return;
        }

        else if(env != environment(zhen->master))
        {
                (zhen->master)->dismiss_array_member(me);
                return;
        }
}

void change_skill_status(string arg)
{
        if(!in_array())
                return;

        if( !stringp(arg)
        || (file_size(SKILL_D(arg)+".c") <= 0) )
                return;

        if( (arg != zhen->type) && zhen->ready)
        {
                message("tell_object",sprintf("【%s】：由于%s沒有使用%s，『%s』的威力消失了。\n",
                        zhen->name,
                        this_object()->name(),
                        to_chinese(zhen->type),
                        zhen->name),
                                zhen->memb);
                zhen->ready = 0;
                return;
        }

        if( (arg == zhen->type) && !zhen->ready)
                check_array_status();
}
// ***************************************


int in_team()
{
        if( classp(oteam) ) {
                oteam->memb -= ({0});
                if( sizeof(oteam->memb) <= 1 )
                        oteam = 0;
        }
        return classp(oteam) && sizeof(oteam->memb);
}

object query_team_leader()
{
        if( !classp(oteam) || !oteam->leader )
                return 0;
        else
                return oteam->leader;
}

object *query_team_member()
{
        if( !classp(oteam) || !oteam->leader )
                return 0;

        oteam->memb -= ({0});
        return oteam->memb;
}

int is_team_member(object who)
{
        if( !who || !in_team() )
                return 0;

        return (member_array(who, oteam->memb) != -1);
}

int is_team_leader()
{
        if( !in_team() )
                return 0;
        return (oteam->leader == this_object());
}

int add_team_member(object who)
{
        if( !who )
                return 0;

        if( in_team() && !is_team_leader() )
                return 0;

        if( !in_team() ) {
                oteam = new(class team);
                oteam->leader = this_object();
                oteam->memb = ({ this_object(), who });

                who->set_team_data(oteam);
                tell_object(this_object(), sprintf("%s應邀加入你的隊伍。\n", who->name()));
                return 1;
        } else {
                oteam->memb -= ({0});
                message("team", sprintf(HIW "【隊伍】%s應邀加入隊伍。\n" NOR, who->name(1)), oteam->memb);
                oteam->memb += ({who});
                (oteam->memb)->set_team_data(oteam);
                return 1;
        }
}

varargs void dismiss_team(object who)
{
        if( !in_team() )
                return;

        if( !who ) {
                if( is_team_leader() ) {
                        oteam->memb -= ({ this_object() });
                        (oteam->memb)->set_team_data(0);
                        message("team", HIW "【隊伍】隊伍解散了。\n", oteam->memb);
                        oteam = 0;
                        return;
                }
                else
                        return (oteam->leader)->dismiss_team(this_object());
        } else {
                if( !is_team_leader() )
                        return;

                tell_object(who, "你脫離隊伍了。\n");
                oteam->memb -= ({ who });
                who->set_team_data(0);
                if( sizeof(oteam->memb) <= 1 ) {
                        tell_object(this_object(), sprintf("由于%s離開隊伍，隊伍解散了。\n",who->name()));
                        oteam = 0;
                        return;
                } else {
                        message("team", sprintf(HIW "【隊伍】%s脫離了隊伍。\n" NOR, who->name(1)), oteam->memb);
                                (oteam->memb)->set_team_data(oteam);
                        return;
                }
        }
}

void check_team()
{
        object env, *ob = ({});

        if( !in_team() )
                return;

        env = environment();
        if( !is_team_leader() ) {
                if( environment(oteam->leader) != env )
                        (oteam->leader)->dismiss_team(this_object());
        } else {
                foreach( object tmp in oteam->memb ) {
                        if( tmp == this_object() )
                                continue;
                        if( environment(tmp) != env )
                                ob += ({tmp});
                }
                if( sizeof(ob) )
                        foreach( object tmp in ob )
                                dismiss_team(tmp);
        }
}

void set_team_data(class team temp)
{
        if( in_team() && is_team_leader() )
                return;
        oteam = temp;
}

object *query_team()
{
        if( !classp(oteam) || !oteam->leader )
                return 0;

        oteam->memb -= ({0});
        return oteam->memb;
}

///////////////////////////////////////////////////////////////////////////////
// 不是隊伍的跟隨
int set_leader(object ob)
{
        if( ob == this_object() )
                //error("set_leader: Cannot set this_object() as leader.\n");
                return 0;
         
        leader = ob;
        
        return 1;
}

object query_leader() { return leader; }

int follow_path(string dir)
{
        if( (origin()==ORIGIN_LOCAL) || (origin()==ORIGIN_CALL_OUT) ) {
                this_object()->remove_all_enemy();
                return GO_CMD->main(this_object(), dir);
        }
}

int follow_me(object ob, string dir)
{
        object me;

        me = this_object();
        if( !living(me) || !ob || ob == me ) return 0;

        if( (ob==leader) && !ob->in_array() && !in_array() && !in_team() )	// array 不能和別人發生 follow 關系	
	{
                // 跟著別人走
                if( query("env/no_follow", ob) &&
                    me->query_dex() / 2 + random(me->query_dex()) < ob->query_dex() ) {
                        tell_object(me, ob->name() +
                                    "走得好快，你一疏神就跟不上了。\n");
                        return 0;
                }
                return follow_path(dir);
        } else if( (in_array() && zhen->master == ob) || (in_team() && ob == oteam->leader) ) 
                // 跟著隊伍的領袖行走
                return follow_path(dir);
}


