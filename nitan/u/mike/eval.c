// This file written by eval command. 
#define COST_TRIM     -8
#define EXPT_TRIM     -4
#include <ansi.h>
#include <command.h>
#include <function.h>
#include <localtime.h>
#include <origin.h>
#include <eval.h>
#include <room.h>
#include <type.h>
#include <user.h>
#include <dbase.h>

inherit F_CLEAN_UP;

void create()
{
        mapping sinfo, einfo;
        int cost, time_exp; 
        float utime, stime, etime;
        string msg;
        object me = this_player();

        sinfo = rusage();
        cost = eval_cost();
        time_exp = time_expression {
s="mike";s[..-1];
        };
        einfo = rusage();
        cost -= eval_cost();

        utime = to_float(einfo["utime"] - sinfo["utime"])/1000000;
        stime = to_float(einfo["stime"] - sinfo["stime"])/1000000;
        etime = to_float(time_exp + EXPT_TRIM)/1000000;

        msg  = sprintf("\n效率評估: %d\n", cost + COST_TRIM);
        msg += sprintf("系統時間: %.6f s\n", stime);
        msg += sprintf("使用時間: %.6f s\n", utime);
        msg += sprintf("運算時間: %.6f s\n", etime);
        
        tell_object(me, msg);
}
