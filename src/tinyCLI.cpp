#include "tinyCLI.h"

// Initialize the static instance pointer
tinyCLI* tinyCLI::instance = nullptr;

// Constructor
tinyCLI::tinyCLI(Stream& input, Command* cmds, int cmdCount)
  : inputStream(input), commands(cmds), commandCount(cmdCount) {
    assignHelpFunction();  // Automatically assign help function
}

// Main function to process input and execute commands
void tinyCLI::processInput() {
  if (inputStream.available()) {
    String input = inputStream.readStringUntil('\n');
    input.trim();
    String command = input.substring(0, input.indexOf(' '));
    String parameters = input.substring(input.indexOf(' ') + 1);
    executeCommand(command, parameters);
  }
}

// Help function to list all available commands
void tinyCLI::printHelp(String params) {
  Serial.println("Available commands:");
  for (int i = 0; i < instance->commandCount; i++) {
    Serial.print(instance->commands[i].name);
    Serial.print(" - ");
    Serial.println(instance->commands[i].description);
  }
}

// Function to assign the help function to the help command
void tinyCLI::assignHelpFunction() {
  instance = this;  // Save the current instance
  for (int i = 0; i < commandCount; i++) {
    if (String(commands[i].name).equals("help")) {
      commands[i].function = tinyCLI::printHelp;
    }
  }
}

// Function to execute a command based on input
void tinyCLI::executeCommand(String input, String parameters) {
  for (int i = 0; i < commandCount; i++) {
    if (input.equals(commands[i].name)) {
      commands[i].function(parameters);  // Pass parameters to the function
      return;
    }
  }
  inputStream.println("Unknown command. Type 'help' for a list of commands.");
}
