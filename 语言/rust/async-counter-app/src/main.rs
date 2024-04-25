mod tui;

use color_eyre::eyre::Result;
use crossterm::event::KeyCode::Char;
use ratatui::{prelude::CrosstermBackend, widgets::Paragraph};
use tui::Event;

// App state
struct App {
    counter: i64,
    should_quit: bool,
}

// App ui render function
fn ui(f: &mut Frame, app: &App) {
    f.render_widget(
        Paragraph::new(format!("Counter: {}", app.counter)),
        f.size(),
    );
}

fn update(app: &mut App, event: Event) {
    match event {
        Event::Key(key) => match key.code {
            Char('j') => app.counter += 1,
            Char('k') => app.counter -= 1,
            Char('q') => app.should_quit = true,
            _ => Action::None,
        },
        _ => {}
    };
}

async fn run() -> Result<()> {
    // ratatui terminal
    let mut tui = tui::Tui::new()?.tick_rate(1.0).frame_rate(30.0);
    tui.enter()?;

    // application state
    let mut app = App {
        counter: 0,
        should_quit: false,
    };

    loop {
        let event = tui.next().await?; // blocks until next event

        if let Event::Render = event.clone() {
            // application render
            tui.draw(|f| {
                ui(f, &app);
            })?;
        }

        // application update
        update(&mut app, event);

        // application exit
        if app.should_quit {
            break;
        }
    }
    tui.exit()?;

    Ok(())
}

#[tokio::main]
async fn main() -> Result<()> {
    let result = run().await;

    result?;

    Ok(())
}
