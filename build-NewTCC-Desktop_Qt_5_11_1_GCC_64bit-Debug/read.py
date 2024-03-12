
import sys
from google.auth.transport.requests import Request
from google.oauth2.credentials import Credentials
from google_auth_oauthlib.flow import InstalledAppFlow
from googleapiclient.discovery import build
from googleapiclient.errors import HttpError

# If modifying these scopes, delete the file token.json.
SCOPES = ['https://www.googleapis.com/auth/spreadsheets']

def get_row(spreadsheet_id, range_name):
  # print(range_name)
  """
  Creates the batch_update the user has access to.
  Load pre-authorized user credentials from the environment.
  TODO(developer) - See https://developers.google.com/identity
  for guides on implementing OAuth2 for the application.
  """
  #creds, _ = google.auth.default()
  creds = Credentials.from_authorized_user_file("token.json", SCOPES)
  # pylint: disable=maybe-no-member
  try:
    service = build("sheets", "v4", credentials=creds)

    result = (
        service.spreadsheets()
        .values()
        .get(spreadsheetId=spreadsheet_id, range=range_name)
        .execute()
    )
    rows = result.get("values", [])
    #print(f"{rows}")

    res_list = []

    for item in rows: 
        if item not in res_list: 
            res_list.append(item[0])
            # print(type(item))
            # print (item, end=" ")
    return res_list
  
  except HttpError as error:
    # print(f"An error occurred: {error}")
    # return error
    return None

def get_values(spreadsheet_id, range_name):
  # print(range_name)
  """
  Creates the batch_update the user has access to.
  Load pre-authorized user credentials from the environment.
  TODO(developer) - See https://developers.google.com/identity
  for guides on implementing OAuth2 for the application.
  """
  #creds, _ = google.auth.default()
  creds = Credentials.from_authorized_user_file("token.json", SCOPES)
  # pylint: disable=maybe-no-member
  try:
    service = build("sheets", "v4", credentials=creds)

    result = (
        service.spreadsheets()
        .values()
        .get(spreadsheetId=spreadsheet_id, range=range_name)
        .execute()
    )
    rows = result.get("values", [])
    #print(f"{rows}")

    # res_list = []

    # for item in rows: 
    #     if item not in res_list: 
    #         res_list.append(item[0])
    #         # print(type(item))
    #         # print (item, end=" ")
    return rows[0]
  
  except HttpError as error:
    # print(f"An error occurred: {error}")
    # return error
    return None
  

  
  
def batch_get_values(spreadsheet_id, _range_names):
  """
  Creates the batch_update the user has access to.
  Load pre-authorized user credentials from the environment.
  TODO(developer) - See https://developers.google.com/identity
  for guides on implementing OAuth2 for the application.
  """
  creds = Credentials.from_authorized_user_file("token.json", SCOPES)
  # pylint: disable=maybe-no-member
  try:
    service = build("sheets", "v4", credentials=creds)
    range_names = [
        # Range names ...
    ]
    result = (
        service.spreadsheets()
        .values()
        .batchGet(spreadsheetId=spreadsheet_id, ranges=range_names)
        .execute()
    )

    rows = result.get("values", [])
    #print(f"{rows}")

    res_list = []

    for item in rows: 
        if item not in res_list: 
            res_list.append(item[0])

    # ranges = result.get("valueRanges", [])
    # print(f"{len(ranges)} ranges retrieved")
    return result
  except HttpError as error:
    print(f"An error occurred: {error}")
    return error

if __name__ == "__main__":
    SAMPLE_SPREADSHEET_ID = open('spreadsheet_id', 'r').readline().strip()

    testCaseIDs = get_row(SAMPLE_SPREADSHEET_ID, sys.argv[1]+"!A2:A")
    # print(f"{testCaseIDs}")
    print(sys.argv[2])

    index = testCaseIDs.index(sys.argv[2])
    # print({index})
    
    row  = get_values(SAMPLE_SPREADSHEET_ID, sys.argv[1]+"!A" + str(index+2) + ":I" + str(index+2))
    print(f"{row}")