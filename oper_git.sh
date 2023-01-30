#  ------------------------------------------------------------------*
# @file    oper_git.sh
# @date    2019-12-02
# @author  七月
# @brief  help git 
#  ------------------------------------------------------------------*
#
#  ------------------------------------------------------------------
# @brief	help 
#  ------------------------------------------------------------------*/
git_help()
{
	echo "./oper_git.sh rebase : 同步最新厂库"
	echo "./oper_git.sh push : 提交修改到厂库"
    git status
}
#  ------------------------------------------------------------------
# @brief	sync repository 
#  ------------------------------------------------------------------*/
git_rebase()
{
    git clean -df
    git checkout -f
    # ./../pull.sh
    git pull --rebase
}

#  ------------------------------------------------------------------
# @brief	merge your changes
#  ------------------------------------------------------------------*/
git_merge()
{
	git status
	read -r -p "是否继续提交? [Y/n] " input
	case $input in
		[yY][eE][sS]|[yY])
			echo "继续提交"
			git add --all
			echo "输入提交信息:"
            echo "1:修改notes"
            echo "2:add or merge code"
			echo "3:add book"
			echo "其他：自由编写commit信息"
			read Buf_commit
            if [ 1 == "$Buf_commit" ];then
                git commit -m "修改notes"
            elif [ 2 == "$Buf_commit" ];then
                git commit -m "修改code"
            elif [ 3 == "$Buf_commit" ];then
                git commit -m "添加书目" 
            else 
                git commit -m "$Buf_commit"
            fi
            # ./../push.sh
            git push origin master
            exit 1
			;;

		[nN][oO]|[nN])
			echo "中断提交"
			exit 1
				;;

		*)
		echo "输入错误，请重新输入"
		;;
	esac
}
#  ------------------------------------------------------------------
  # @brief       loop check device node
#  ------------------------------------------------------------------*/

if [ ! -n "$1" ] ;then
git_help
fi

if [ rebase == "$1" ];then
git_rebase
fi

if [ push == "$1" ];then
git_merge
fi

