use anyhow::Result;
use thirtyfour::prelude::*;
use tokio::time::{sleep, Duration};

#[tokio::main]
async fn main() -> Result<()> {
    // Define username and password
    let username_str = "221040100409";
    let password_str = "2423167309-Zzq";

    // Initialize WebDriver
    let driver = WebDriver::new("http://localhost:9515", DesiredCapabilities::chrome()).await?;

    // Open the browser and navigate to the specified URL
    driver
        .goto("https://jwglxt.haut.edu.cn/jwglxt/xtgl/login_slogin.html")
        .await?;

    // Wait for the username input field to load and enter username and password
    let username = driver.find(By::Id("yhm")).await?;
    username.send_keys(username_str).await?;
    let password = driver.find(By::Id("mm")).await?;
    password.send_keys(password_str).await?;

    // Click the login button
    let login_button = driver.find(By::Id("dl")).await?;
    login_button.click().await?;
    sleep(Duration::from_secs(1)).await;

    // Wait for the "Information Query" menu to appear and click it
    driver.find(By::LinkText("信息查询")).await?.click().await?;
    sleep(Duration::from_secs(1)).await;

    // Wait for the "Personal Course Schedule Query" menu to appear and click it
    driver
        .find(By::LinkText("个人课表查询"))
        .await?
        .click()
        .await?;
    sleep(Duration::from_secs(1)).await;

    // 切换到新打开的窗
    let handles = driver.windows().await?;
    driver.switch_to_window(handles[1].clone()).await?;
    

    // Find the PDF button and click it
    sleep(Duration::from_secs(2)).await;
    driver.find(By::Id("shcPDF")).await?.click().await?;

    // Wait for 10 seconds to allow the download to complete
    sleep(Duration::from_secs(10)).await;

    // Close the browser
    driver.quit().await?;

    Ok(())
}
