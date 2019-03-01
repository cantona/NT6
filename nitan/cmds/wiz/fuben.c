// This program is a part of NITAN MudLIB
// Written by Lonely@nitan.org (16/05/2008)
// fuben.c 副本管理指令

#include <ansi.h>

inherit F_CLEAN_UP;

int help (object me);
int main(object me,string arg)
{
        int i, j;
        string cmd;
        string fbname;
        string owner;
        string *ks, *os;
        mapping all, data, temp;
        string msg = "";

        if( !SECURITY_D->valid_grant(me, "(wizard)") )
                return 0;

        if( !arg ) {
                help( me );
                return 1;
        }

        if( sscanf(arg,"%s %s %s",cmd, fbname, owner) != 3 &&
            sscanf(arg,"%s %s",cmd, fbname) != 2 )
                cmd = arg;

        all  = FUBEN_D->query_fuben_all();
        data = FUBEN_D->query_fuben_data();
        if( !stringp(fbname) ) {
                if( !all ) return notify_fail("泥潭現在沒有任何副本。\n");
                msg += "泥潭現在開啟的副本空間如下：\n";
                msg += "＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝\n";
                ks = keys(all);
                for( i=0;i<sizeof(ks);i++ ) {
                        temp=all[ks[i]];
                        if( mapp(temp) && sizeof(temp) ) {
                                os = keys(temp);
                                for( j=0;j<sizeof(os);j++ )
                                        msg += sprintf("副本名稱：%-33s剩余時間：%s\n",
                                                data[ks[i]]["name"]+"<"+ks[i]+">("+os[j]+")",
                                                appromix_time(temp[os[j]] - time()) );
                        }

                }
                me->start_more(msg);
                return 1;
        } else {
                if( cmd == "open" ) {
                        FUBEN_D->open_fuben(me, fbname);
                        return 1;
                } else if( cmd == "close" ) {
                        FUBEN_D->close_fuben(me, fbname);
                        return 1;
                }

                if( fbname != "all" && (undefinedp(data[fbname]) ||
                    undefinedp(all[fbname])) )
                        return notify_fail("泥潭現在沒有這個副本。\n");

                if( cmd == "list" ) {
                        msg += sprintf("泥潭現在開啟的%s副本空間如下：\n", (fbname=="all")?"所有":data[fbname]["name"]);
                        msg += "＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝\n";
                        if( fbname == "all" ) {
                                ks = keys(data);
                                for( i=0;i<sizeof(ks);i++ ) {
                                        msg += sprintf("副本名稱：%-26s組隊要求：%-8s任務時間：%s\n",
                                               data[ks[i]]["name"]+"<"+ks[i]+">",
                                               (!undefinedp(data[ks[i]]["team"]))?"必須":
                                               (!undefinedp(data[ks[i]]["single"])?"單人":"任意"),
                                               appromix_time(to_int(data[ks[i]]["time"])) );
                                }
                        } else {
                                temp = all[fbname];
                                ks = keys(temp);
                                for( i=0;i<sizeof(ks);i++ ) {
                                        msg += sprintf("副本名稱：%-33s剩余時間：%s\n",
                                               data[fbname]["name"]+"<"+fbname+">("+ks[i]+")",
                                               appromix_time(temp[ks[i]] - time()) );
                                }
                        }
                        me->start_more(msg);
                        return 1;
                } else if( cmd == "dest" ) {
                        if( !stringp(owner) ) {
                                ks = keys(all[fbname]);
                                for( i=0;i<sizeof(ks);i++ )
                                        FUBEN_D->clear_fuben(fbname, ks[i]);
                                write("OK.\n");
                                return 1;

                        } else {
                                FUBEN_D->clear_fuben(fbname, owner);
                                write("OK.\n");
                                return 1;
                        }

                } else {
                        help(me);
                        return 1;
                }
        }
        return 1;
}

int help (object me)
{
                      write(@HELP
指令格式 : fuben list [副本名稱]
           fuben dest  副本名稱  [副本主人]

fuben list [all]              查看當前遊戲中所有的副本詳細信息
fuben list 副本名稱           查看指定副本的詳細信息
fuben open|dest all|副本名稱  查看指定副本的詳細信息
fuben dest 副本名稱           銷毀指定類型副本的所有副本
fuben dest 副本名稱 副本主人  銷毀指定類型副本的某人副本

HELP );
                      return 1;
}