#pragma once

class iGame {
public:
  iGame() = default;
  virtual ~iGame() = default;
  iGame(const iGame& other) = delete;
  iGame& operator=(const iGame& other) = delete;
  iGame(iGame&& other) = delete;
  iGame& operator=(iGame&& other) = delete;

  virtual void RunLoop() = 0;

protected:
  virtual void ProcessInput() = 0;
  virtual void UpdateGame() = 0;
  virtual void GenerateOutput() = 0;
};