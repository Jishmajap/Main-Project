const isLogin = () => {
    if(!localStorage.getItem("isLogin")){
        return true
    }else{
        return false
    }
}

export default isLogin;